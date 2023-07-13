#include<iostream>
#include<fstream>
#include<malloc.h>
#include<fftw3.h>
#include<cmath>

using namespace std;

const float pi = 3.1415923;
float scale=0.0;
float T=0.0;
float st=0.0;

void gaussian(fftw_complex *arr, int n, float mean, float stdev, float beg, float end, float *x)
{
    st=(end-beg)/n;
    float f0=1000;
    for(int i=0;i<n;i++)
    {
      x[i] = beg + st*i;
      arr[i][0] = exp(-1*pow(x[i]-mean,2)/(2*pow(stdev,2)));
      arr[i][1] = 0;
    }
}
void square(fftw_complex *arr, int n, float width, float height)
{
  float hw=width/2;
  for(int i=0;i<n;i++)
  {
    arr[i][0]=0;
    arr[i][1]=0;
  }
  for(int i=n/2-hw;i<n/2+hw;i++)
  {
    arr[i][0]=height;
    arr[i][1]=0;
  }
}
void triangle(fftw_complex *arr, int n, float width, float height)
{
  float hw=width/2;
  float slope=height/width;
  for(int i=0;i<n;i++)
  {
    arr[i][0]=0;
    arr[i][1]=0;
  }
  for(int i=n/2-hw;i<n/2;i++)
  {
    arr[i][0]=slope*abs(n/2-hw-i);
    arr[i][1]=0;
  }
  for(int i=n/2;i<n/2+hw;i++)
  {
    arr[i][0]=height-slope*abs(n/2-hw-i);
    arr[i][1]=0;
  }
}
void step(fftw_complex *arr, int n, float step_size, int trip)
{
  for(int i=0;i<trip;i++)
  {
    arr[i][0]=0;
    arr[i][1]=0;
  }
  for(int i=trip;i<n;i++)
  {
    arr[i][0]=step_size;
    arr[i][1]=0;
  }
}

void menu(fftw_complex *arr, int n,float *x)
{
  int c;
  float beg,end,mean,stdev;          //Variables for Gaussian
  float height,width;               //Variables for square and triangle
  float step_size,trip;             //Variables for step function
  cout<<"Enter a choice: ";
  cin>>c;
  switch(c)
  {
    case 0: cout<<"You have chosen a Gaussian input signal."<<endl;
            cout<<"Enter the beginning x value: ";
            cin>>beg;
            cout<<"Enter the ending x value: ";
            cin>>end;
            cout<<"Enter the mean of the distribution: ";
            cin>>mean;
            cout<<"Enter the standard deviation of the distribution: ";
            cin>>stdev;
            scale=1;
            T=end-beg;
            gaussian(arr,n,mean,stdev,beg,end,x);
            break;
    case 1: cout<<"You have chosen a square wave input signal."<<endl;
            cout<<"Enter the width: ";
            cin>>width;
            cout<<"Enter the height: ";
            cin>>height;
            square(arr,n,width,height);
            scale=width;
            break;
    case 2: cout<<"You have chosen a triangular wave input signal. "<<endl;
            cout<<"Enter the width: ";
            cin>>width;
            cout<<"Enter the height: ";
            cin>>height;
            triangle(arr,n,width,height);
            scale=width/2;
            break;
    case 3: cout<<"You have chosen a step function input signal. "<<endl;
            cout<<"Enter step size: ";
            cin>>step_size;
            cout<<"Enter trip point: ";
            cin>>trip;
            scale=step_size;
            step(arr,n,step_size,trip);
  }
}

void arrange(fftw_complex *arr, int n)
{
  for(int i=0;i<n/2;i++)
  {
    float temp0 = arr[i][0];
    float temp1 = arr[i][1];
    arr[i][0]=arr[n/2+i][0];
    arr[i][1]=arr[n/2+i][1];
    arr[n/2+i][0]=temp0;
    arr[n/2+i][1]=temp1;
  }
}
double max(double *arr, int n)
{
  double m=arr[0];
  for(int i=1;i<n;i++)
  {
    if(arr[i]>m)
    {
      m=arr[i];
    }
  }
  return m;
}
int deviate(double *arr, int n)
{
  int pos=-1;
  double hmax=0.5*max(arr,n);
  for(int i=n/2;i<n;i++)
  {
    if(arr[i]<hmax)
    {
      pos=i;
      break;
    }
  }
  int dev=abs(n-2*pos);
  return dev;
}
int main()
{
  ofstream ofile,ofilep;
  ofstream ifile;
  ofile.open("output.txt");
  ofilep.open("power.txt");
  ifile.open("input.txt");
  fftw_complex *in, *out;
  double *out_abs,*p;
  float *x;
  fftw_plan p1;
  int n=0;
  char c;
  cout<<"Enter the number of elements: ";
  cin>>n;
/*
  float beg,end,step,mean,stdev,range;

  cout<<"Enter starting element: ";
  cin>>beg;
  cout<<"Enter ending element: ";
  cin>>end;
  cout<<"Enter mean: ";
  cin>>mean;
  cout<<"Enter standard deviation: ";
  cin>>stdev;
*/
  in=(fftw_complex *) fftw_malloc(sizeof(fftw_complex)*n);
  out=(fftw_complex *) fftw_malloc(sizeof(fftw_complex)*n);
  out_abs=(double *) malloc(sizeof(double)*n);
  p=(double *) malloc(sizeof(double)*n);
  x=(float *) malloc(sizeof(float)*n);
  menu(in,n,x);
/*
  range=end-beg;
  step=range/float(n);
  for(int i=0; i<n; i++)
  {
    float elt=beg+step*i;
    in[i][0] = exp((-1)*pow(elt-mean,2)/(2*pow(stdev,2)))*(1/sqrt(n));
    in[i][1] =0;
  }
*/
  p1=fftw_plan_dft_1d(n, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
  fftw_execute(p1);
  cout<<"Input array: ";
  for(int i=0;i<n;i++)
  {
    cout<<i<<" "<<in[i][0]<<" "<<in[i][1]<<endl;
    ifile<<x[i]<<" "<<in[i][0]<<endl;
  }
  fftw_free(in);
  cout<<endl;
  cin>>c;

  arrange(out,n);
  cout<<"Output array: ";
  for(int i=0;i<n;i++)
  {
    double norm = sqrt(pow(out[i][0],2)+pow(out[i][1],2));
    out_abs[i]=norm;
    cout<<i<<" "<<out[i][0]<<" "<<out[i][1]<<" "<<norm<<endl;
    ofile<<i<<" "<<i/(n*st)<<" "<<out[i][0]<<" "<<out[i][1]<<" "<<norm/scale<<endl;
  }

  cout<<"Absolute values: ";
  for(int i=0;i<n;i++)
  {
    cout<<i<<" "<<out_abs[i]<<endl;
  }

  cout<<endl;
  int hmax=deviate(out_abs,n);
  cout<<hmax<<endl;
  for(int i=0;i<n;i++)
  {
    p[i] = pow(out_abs[i],2)+pow(out_abs[n-1-i],2);
    ofilep<<i<<" "<<p[i]<<endl;
  }
  ofile.close();
  ifile.close();
  ofilep.close();
  fftw_destroy_plan(p1);
  fftw_free(out);
  delete out_abs;
  delete p;
  return 0;
}
