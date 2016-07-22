#include "TRACSInterface.h"
//#include <iostream>
 #include <thread>

//using namespace std;
static const int num_threads = 2;
  
      //This function will be called from a thread
  
      void call_from_thread(int tid) {
          //std::cout << "Launched by thread " << tid << std::endl;
      	 //std::string fnm="Config.TRACS";

	      	 if(tid==0){
	      	 		std::string fnm1="Config.TRACS";
	      	 	std::cout << "Thread1!" << std::endl;
	      	 	TRACSInterface *TRACSsim = new TRACSInterface(fnm1);
	      	 	std::cout << "Made it t1!" << std::endl;

	         	TRACSsim->loop_on(1);
	      	 }
	      	 if(tid==1){
	      	 	std::string fnm2="Config.TRACS";
	      	 	std::cout << "Thread2!" << std::endl;
	      	 	for(int i=0; i<100000000; i++);
	      	 	TRACSInterface *TRACSsim2 = new TRACSInterface(fnm2);
	      	 	std::cout << "Made it t2!" << std::endl;

	      	 	TRACSsim2->loop_on(2);

	      	 }
      	 }

      	
     

int main()
{
	//test
	std::cout << "It compiled, yaay!" << std::endl;
	//Interface to TRACS
	//std::string fnm="Config.TRACS";
	//TRACSInterface TRACSsim(fnm);
	//TRACSInterface *TRACSsim = new TRACSInterface( fnm ); //CORRECT
/*	TRACSsim->set_zPos(30);
	TRACSsim->set_yPos(30);
	TRACSsim->set_vBias(400);
	TRACSsim->calculate_fields();
	TRACSsim->set_vBias(400);
	TRACSsim->set_trappingTime(std::numeric_limits<double>::max()-100);
	TRACSsim->set_neffType("Linear");
	TRACSsim->set_carrierFile("etct.carriers");
	TRACSsim->set_NeffParam({-25.,0.02,0.22,33.,0.,120.,220.,300});
	TRACSsim->calculate_fields();
	TRACSsim->simulate_ramo_current();
	TRACSsim->GetItRamo();
	TRACSsim->GetItRc();
	TRACSsim->GetItConv();
	*/
	//TRACSsim->loop_on("v");
	//TRACSsim->loop_on("y");
	//TRACSsim->loop_on("y","v","z");
	//TRACSsim->loop_on("v","y","z");
	std::thread t[num_threads];
 
         //Launch a group of threads
         for (int i = 0; i < num_threads; ++i) {
             t[i] = std::thread(call_from_thread, i);
         }
 
         std::cout << "Launched from the main\n";
 
         //Join the threads with the main thread
         for (int i = 0; i < num_threads; ++i) {
             t[i].join();
         }
	//TRACSsim->loop_on("v","e");
	//TRACSsim->loop_on("v","y");
	//TRACSsim->loop_on("c");

	
	//std::cout<<"i_ramo:"<<TracsSim.GetItRamo()<<std::endl;
	//TracsSim.set_carrierFile("etct.carriers");
	//TRACSInterface* TracsSim = new TRACSInterface("Config.TRACS");


	//test
	std::cout << "A bit slow!" << std::endl;

	
	//while(true);
	
	return 0;
	
}
