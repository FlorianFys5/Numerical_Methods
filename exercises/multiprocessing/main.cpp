#include<iostream>
#include<cmath>
#include<vector>
#include<thread>
struct data { int a,b; double sum;};
void harm(data& arg){
	int a=arg.a,b=arg.b; // you better work
	double sum=0;        // with thread-local variables
	for(int i=a;i<b;i++)sum+=1.0/i;
	arg.sum=sum; // only write once into memory
	}
int main(int argc, char* argv[]){
    int nthreads = 1, nterms = (int)1e8; /* default values */
for(int i=0;i<argc;i++) {
   std::string arg = argv[i];
   if(arg=="-threads" && i+1<argc) nthreads=std::stoi(argv[i+1]);
   if(arg=="-terms" && i+1<argc) nterms=std::stoi(argv[i+1]);
   }
   std::vector<data> params(nthreads);
for(int i=0;i<nthreads;i++) {
   params[i].a = 1 + nterms/nthreads*i;
   params[i].b = 1 + nterms/nthreads*(i+1);
   }
params[params.size()-1].b=nterms+1; /* the enpoint might need adjustment */
std::vector<std::thread> threads;
threads.reserve(nthreads); // reserve empty slots for our threads

for(int i=0;i<nthreads;i++) {
   threads.emplace_back(harm,std::ref(params[i]));
   }
for(auto &thread : threads) thread.join();
double total=0; for(auto &p : params) total+=p.sum;
std::cout << total << "\n";
return 0;
}