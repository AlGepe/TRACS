#include <cuda.h>
#include <typeinfo>
#include "ElectricField.cuh"

/*
__global__ void d_getEfield(ElectricField *meshfield, 
														std::vector<std::vector<double> > *samplePoints,
														std::vector<double> *eValues)
{
	int id = threadIdx.x;
	std::vector<double> thisPoint(2, 0);
	thisPoint[0] = 3.; //samplePoints[id][0];
	thisPoint[1] = 10.;  //samplePoints[id][1];
	meshfield->getEvalue(&thisPoint, &eValues);
	eValues[id] = meshfield->getEvalue(thisPoint);
}
*/

int main()
{
	// Create E_field
	srand ( time(NULL) );
	ElectricField eField(0., 10., 2., 24., 100, 100);
	ElectricField* h_p_eField = &eField;
	ElectricField *d_p_eField;	
	// Initialize sample points
	std::vector< std::vector<double> > h_samples(20, std::vector<double>(2, 0));
	for(int i=0; i<20; i++){
		h_samples.at(i).at(0) = rand() % 10;
		h_samples.at(i).at(1) = rand() % 22 + 2;
	}
	std::cout << eField.get_grid().at(0).size() << std::endl;
	std::vector< std::vector<double> > *d_samplesPtr;
	std::vector< double > h_result(20, 0), *d_values;
	
	int sampleVct_size = h_samples.size() * h_samples[0].size() * sizeof(double); //usefull number
	int resultVct_size = h_result.size() * sizeof(double); //usefull number

	// Get device memory ready
	cudaMalloc((void **) &d_samplesPtr, sampleVct_size);
	cudaMemcpy((void *) d_samplesPtr, (void *) &h_samples, sampleVct_size, cudaMemcpyHostToDevice);
	cudaMalloc((void **) &d_values, resultVct_size);
	cudaMemcpy((void *) d_values, (void *) &h_result, resultVct_size, cudaMemcpyHostToDevice);
	cudaMalloc((void **)&d_p_eField, sizeof(ElectricField));	
	cudaMemcpy((void *)d_p_eField, (void *) h_p_eField, sizeof(ElectricField), cudaMemcpyHostToDevice);

	for(int j=0; j<20; j++){
	std::cout << h_samples.at(j).at(0) << std::endl;
	std::cout << eField.getEvalue(h_samples.at(j)) << std::endl;
	} // On host

	// clean device
	cudaFree((void *) d_samplesPtr);
	cudaFree((void *) d_p_eField);
	cudaFree((void *) d_values);
	return 0;
}
