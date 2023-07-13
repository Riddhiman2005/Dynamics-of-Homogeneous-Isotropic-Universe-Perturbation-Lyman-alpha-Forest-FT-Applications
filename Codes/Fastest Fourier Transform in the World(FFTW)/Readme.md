
Let us consider an array of rank $d$ whose dimensions are $n_0 \times n_1 \times n_2 \times ... \times n_{d-1}$. If we specify a location in the array by a tuple of indices, one for each dimension, say:
        $(i_0,i_1,i_2,i_3,...,i_{d-1})$. Then the position of the element is given by
       ![lagrida_latex_editor](https://github.com/Riddhiman2005/Dynamics-of-the-Homogeneous-Isotropic-Universe-Metric-Perturbations-and-Lyman-alpha-Forest/assets/130882317/a8cff51d-ba97-4c6b-8a71-f25f1b2fc9da)

        
       
      <br>  
   
    After the plans have been executed, they are to be destroyed with the {\textsans fftw\_destroy\_plan} command.
        
        Some common plans which are available in the library are:

• fftw plan fftw plan dft 1d(int n0, fftw complex *in, fftw complex *out, int sign, unsigned flags);<br>
• fftw plan fftw plan dft 2d(int n0, int n1, fftw complex *in, fftw complex *out, int sign, unsigned flags);<br>
• fftw plan fftw plan dft 3d(int n0, int n1, int n2, fftw complex *in, fftw complex *out, int sign, unsigned flags);<br>
• fftw plan fftw plan dft(int rank, const int *n, fftw complex *in, fftw complex *out, int sign, unsigned flags); <br>
