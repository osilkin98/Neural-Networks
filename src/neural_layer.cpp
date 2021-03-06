//
// Created by Oleg on 6/14/2018.
//

#include <memory>
#include <exception>
#include "neural_layer.h"
#include "matrix_operators.h"
#include "namespaces.h"

using namespace neural_networks::utilities;

void neural_networks::utilities::NeuralLayer::clean() {
    delete data;
    data = nullptr;
    delete bias;
    bias = nullptr;
    delete weights;
    weights = nullptr;
}

neural_networks::utilities::NeuralLayer::NeuralLayer(
        const neural_networks::utilities::NeuralLayer *input,
        const size_t layer_size,
        std::string label
) : input(input), N(layer_size), label(label) {
    try {
        data = new NeuralMatrix(N);
        weights = matrix_operators::create_randomized_matrix(N, input -> N);
        bias = matrix_operators::create_randomized_matrix(N);
    } catch (std::bad_alloc& error) {
        std::cerr << "NeuralLayer object at <" << this << "> failed to allocate memory.\n";
        delete data;
        delete weights;
        delete bias;
    }
}


neural_networks::utilities::NeuralLayer::NeuralLayer(const size_t layer_size,
                                                     const size_t previous_layer_size,
                                                     std::string label)
        : N(layer_size), label(label), input(nullptr) {

    data = new NeuralMatrix(layer_size, 1);
    if(previous_layer_size) { // if we have a specifed size for the previous layer
        weights = matrix_operators::create_randomized_matrix(layer_size, previous_layer_size);
        bias = matrix_operators::create_randomized_matrix(layer_size);

    } else { // otherwise this is the first (input) layer, so we don't create weights + bias
        bias = nullptr;
        weights = nullptr;
    }
}



// copy constructor
NeuralLayer::NeuralLayer(const NeuralLayer &other) : N(other.N) {
    // N should be the same for each matrix
    data = new NeuralMatrix(other.data -> N, 1);
    // this is only in the case of the input matrix, which has no weight or bias matrix
    if(!other.weights) {
        return;
    }
    // Matrix copy constructor should be copying not replacing
    bias = new Matrix<long double>(*other.bias); // for all the matrices
    weights = new Matrix<long double>(*other.weights);
}

// basic destructor just deletes the NeuralMatrix Objects
NeuralLayer::~NeuralLayer() {
    delete weights;
    delete bias;
    delete data;
}

// This is to set the other object to the calling object
NeuralLayer& NeuralLayer::operator=(const NeuralLayer& other) {
    std::cout << "Assignment operator called\n";
    if(this != &other) {
        std::cout << this << " != " << &other << "\n";
        // Matrix<Neuron *>::operator=(other);

        std::unique_ptr< Matrix<long double> > t_weights(new Matrix<long double>(*other.weights)),
                t_bias(new Matrix<long double>(*other.bias));
        std::unique_ptr< NeuralMatrix > t_data(new NeuralMatrix(*other.data));


        delete weights;
        weights = t_weights.release();
        delete bias;
        bias = t_bias.release();
        delete data;
        data = t_data.release();
        N = other.N;
    }
    return *this;
}

// this just performs the forward pass operation for one Layer from the previous layer
void NeuralLayer::update() const {
    if(weights -> M != input -> data -> N) {
        std::cerr << "During update operation, bias M [" << bias -> N << "] at " << bias
                  << " in object " << this << " does not match input vector size N [" << input -> data -> N
                  << "] at " << input -> data << '\n';
    }
    register size_t i;
    long double sum;
    if(input -> bias) { // if we're not dealing with the input layer
        for(register size_t elem = 0; elem < N; ++elem) {
            sum = bias -> matrix[elem][0];
            for(i = 0; i < bias -> M; ++i) {
                sum += weights -> matrix[elem][i] *
                       input -> data -> matrix[i][0] -> function;
            }
            data -> matrix[elem][0] -> set(sum);
        }
    } else {  // operates on data field instead of function
        for(register size_t elem = 0; elem < N; ++elem) {
            sum = bias -> matrix[elem][0];
            for(i = 0; i < bias -> M; ++i) {
                sum += weights -> matrix[elem][i]  *
                       input -> data -> matrix[i][0] -> data;
            }
            data -> matrix[elem][0] -> set(sum);
        }
    }
}


// print function
void NeuralLayer::print() const {
    std::cout << "\nData Vector: " << data << "\n\n";
    data -> print();
    if(bias) {
        std::cout << "\nWeight Matrix: " << weights << "\n\n";
        weights -> print();
        std::cout << "\nBias Vector: " << bias << "\n\n";
        bias -> print();
    }
    std::cout << std::endl;
}


