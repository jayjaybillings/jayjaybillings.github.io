/*----------------------------------------------------------------------------
/
/ Filename: fits_wavelet.c
/ Author: Jay Billings
/ Author's email: jayjaybillings@gmail.com
/ Description: This program will perform a Debauchies wavelet transform on 
/              an input image and turn off the wavelet coefficients up to 
/              a certain percentage of the total size.
/
/              Usage:
/                 ./fits_wavelet <image> <limit>
/
/                 <image> should be an image in FITS format and <limit>
/                 should be a number between 0.0 and 1.0.
/
/              Output: 
/                 filtered_<image>
/
/                 The output image is also in the FITS format and is readily
/                 viewable in FV, available from the NASA website, or the 
/                 Sky Image Processor, useable as a java applet from Dr.
/                 John Simonetti, Virginia Tech,
/ 
/                 http://www.phys.vt.edu/~jhs/SIP.
/
/              This code requires the CFITSIO library and the GNU Scientific
/              Library. Both are freely available on the internet. This code
/              compiles fine with gcc-4.1.2 using
/
/                 gcc -o fits_wavelet fits_wavelet.c -lm -lgsl -lgslcblas 
/                  -lcfitiso
/
/ Copyright (c) 2008       Jay Jay Billings
/
/ This program is free software; you can redistribute it and/or modify
/ it under the terms of the GNU General Public License as published by
/ the Free Software Foundation; either version 2 of the License, or
/ (at your option) any later version.
/
/ This program is distributed in the hope that it will be useful,
/ but WITHOUT ANY WARRANTY; without even the implied warranty of
/ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/ GNU General Public License for more details.
/
/ You should have received a copy of the GNU General Public License
/ along with this program; if not, write to the Free Software
/ Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
/
/ The license is also available at:
/
/		http://www.gnu.org/copyleft/gpl.html .
/
/ Date: 2008/03/24
/
*///--------------------------------------------------------------------------

#include <string.h>
#include <stdio.h>
#include <fitsio.h>
#include <gsl/gsl_wavelet.h>
#include <gsl/gsl_sort.h>
#include <math.h>

void read_image(double *,char *,int []);
void write_image(double *, char *, int []); 

int main(int argc, char *argv[]) {
  
    int i, j, size[3], a; 
    double f, limit, *pixels, *pixels_copy;
    gsl_wavelet *w;
    gsl_wavelet_workspace *work; 
    size_t *p;

    // Check to make sure that the inputs are OK.
    if (argc < 3) {
       printf("You need to specify a file! \n\nUsage: ");
       printf("\t fits_wavelet <input_file> <limit>\n\n");
       exit(0);
    }
    f = atof(argv[2]);
    if (f >= 1.0) {
       printf("The limit must be between 0.0 and 1.0!\n\n");
       printf("Try something else! (Like 0.85...)\n");
       exit(0);
    }

    // Allocate some storage arrays. The maximum size is currently
    // set at 1024*1024, or 2^20, initilized to zero.
    if (!(pixels = calloc(1024*1024,sizeof(double)))) {
         printf("Memory allocation error\n");
         exit(0);
    }
    if (!(pixels_copy = calloc(1024*1024,sizeof(double)))) {
         printf("Memory allocation error\n");
         exit(0);
    }
    if (!(p = malloc(1024*1024*sizeof(size_t)))) {
         printf("Memory allocation error\n");
         exit(0);
    }

    // Read the image into the pixels array.
    read_image(pixels,argv[1],size);
    
    // Allocate the wavelet workspace.
    w = gsl_wavelet_alloc(gsl_wavelet_daubechies,20);
    work = gsl_wavelet_workspace_alloc(1024*1024); 

    // Perform the wavelet transfer.
    gsl_wavelet_transform_forward(w,pixels,1,1024,work);

    // Make a copy of the pixels array and sort it.
    for (i = 0; i < size[2]; ++i) {
        pixels_copy[i] = fabs(pixels[i]);
 
    } 
    gsl_sort_index(p,pixels_copy,1,size[0]*size[1]);
    
    // Loop over the wavelet coefficients and turn them off
    // up to a certain limit.
    limit = (double) size[2] * f;
    for (i = 0; i < (int) limit; ++i) {
        pixels[p[i]] = 0.0;
    }

    // Perform the inverse transform.
    gsl_wavelet_transform_inverse(w,pixels,1,1024,work);

    // Write the image. 
    write_image(pixels,argv[1],size);

    // Free all the memory and exit.
    gsl_wavelet_free(w);
    gsl_wavelet_workspace_free(work);
    free(pixels);free(pixels_copy);free(p);
    return 0;
}

// This subroutine was adapted from documentation provided on the FITSIO website.
void read_image(double *pixels_vector, char *filename, int size[3])
{
    fitsfile *fptr;   /* FITS file pointer, defined in fitsio.h */
    int status = 0;   /* CFITSIO status value MUST be initialized to zero! */
    int bitpix, naxis, ii, anynul,a;
    long naxes[2] = {1,1}, fpixel[2] = {1,1};
    double *pixels;
    char format[20], hdformat[20];

    /*if (argc != 2) {
      printf("Usage:  imlist filename[ext][section filter] \n");
      printf("\n");
      printf("List the the pixel values in a FITS image \n");
      printf("\n");
      printf("Example: \n");
      printf("  imlist image.fits                    - list the whole image\n");
      printf("  imlist image.fits[100:110,400:410]   - list a section\n");
      printf("  imlist table.fits[2][bin (x,y) = 32] - list the pixels in\n");
      printf("         an image constructed from a 2D histogram of X and Y\n");
      printf("         columns in a table with a binning factor = 32\n");
      return(0);
    }*/

    if (!fits_open_file(&fptr, filename, READONLY, &status))
    {
        if (!fits_get_img_param(fptr, 2, &bitpix, &naxis, naxes, &status) )
        {
          if (naxis > 2 || naxis == 0)
             printf("Error: only 1D or 2D images are supported\n");
          else
          {
            /* get memory for 1 row */
            if (!(pixels = malloc(naxes[0] * sizeof(double)))) {
                printf("Memory allocation error\n");
                exit(0);
            }

            if (bitpix > 0) {  /* set the default output format string */
               strcpy(hdformat, " %7d");
               strcpy(format,   " %7.0f");
            } else {
               strcpy(hdformat, " %15d");
               strcpy(format,   " %15.5f");
            }

            //printf("\n      ");          /* print column header */
            //for (ii = 1; ii <= naxes[0]; ii++)
            //   printf(hdformat, ii);
            //printf("\n");                /* terminate header line */

            /* loop over all the rows in the image, top to bottom */
            a = 0;
            for (fpixel[1] = naxes[1]; fpixel[1] >= 1; fpixel[1]--)
            {
               if (fits_read_pix(fptr, TDOUBLE, fpixel, naxes[0], NULL,
                    pixels, NULL, &status) )  /* read row of pixels */
                  break;  /* jump out of loop on error */

            //   printf(" %4d \n",fpixel[1]);  /* print row number */
               for (ii = 0; ii < naxes[0]; ii++) {
                  pixels_vector[a] = pixels[ii];
//                  printf(format, pixels_vector[a]);   /* print each value  */
 //                 printf(" %d\n",a);                    /* terminate line */
                  ++a;
               }
            }
            size[0] = naxes[0];
            size[1] = naxes[1];
            size[2] = naxes[0]*naxes[1];
            free(pixels);
          }
        }
        fits_close_file(fptr, &status);
    }

    if (status) {
       fits_report_error(stderr, status); /* print any error message */
       exit(0);
    }
    //return(status);
    return;
}

void write_image(double *pixels_vector, char *f1, int size[3]) {

    fitsfile *infptr, *outfptr;   /* FITS file pointer, defined in fitsio.h */
    int status = 0;   /* CFITSIO status value MUST be initialized to zero! */
    int ii = 1;
    char f2[200];
    long size_l[2], fpixel[2] = {1,1};
    void *pix_ptr = &pixels_vector;

    size_l[0] = (long) size[0];
    size_l[1] = (long) size[1];

    sprintf(f2,"filtered_%s",f1);

    /* Create the output file */
    if (!fits_create_file(&outfptr, f2, &status) ) {
       if (!fits_create_img(outfptr,32,2,size_l,&status)) {
          if (!fits_write_pix(outfptr,TDOUBLE,fpixel,(long) size[2],pixels_vector \
           ,&status)) {
          if (status == END_OF_FILE) status = 0;
          }
          //printf("Write status: %d \n",status); 
       }
       fits_close_file(outfptr,  &status);
    }

    return;
}
