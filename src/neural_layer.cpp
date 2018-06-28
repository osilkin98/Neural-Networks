//
// Created by Oleg on 6/14/2018.
//

#include "neural_layer.h"


void NeuralLayer::clean() {
    delete data;
    data = nullptr;
    delete bias;
    bias = nullptr;
    delete weights;
    weights = nullptr;
}

NeuralLayer::NeuralLayer(const size_t layer_size, const size_t previous_layer_size) : N(layer_size) {
    data = new NeuralMatrix(layer_size, 1);
    if(previous_layer_size) { // if we have a specifed size for the previous layer
        weights = new NeuralMatrix(layer_size, previous_layer_size, false, true);
        bias = new NeuralMatrix(layer_size, 1, false, true);

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
    bias = new NeuralMatrix(other.bias -> N, 1); // for all the matrices
    weights = new NeuralMatrix(other.weights -> N, other.weights -> M);

    size_t N = other.data -> N, M = other.weights -> M;
    register size_t i, j;

    for(i = 0; i < N; ++i) {
        data -> matrix[i][0] = other.data -> matrix[i][0];
        bias -> matrix[i][0] = other.bias -> matrix[i][0];
        for(j = 0; j < M; ++j) {
            weights -> matrix[i][j] = other.weights -> matrix[i][j];
        }
    }
}

// basic destructor just deletes the NeuralMatrix Objects
NeuralLayer::~NeuralLayer() {
    delete weights;
    delete bias;
    delete data;
}

// This is to set the other object to the calling object
NeuralLayer& NeuralLayer::operator=(const NeuralLayer& other) {
    // this code could probably be cleaned up but it's too much extra overhead to deal with for something that isn't changing
    NeuralMatrix *temp = weights;
    weights = other.weights;
    delete temp;
    temp = bias;
    bias = other.bias;
    delete temp;
    temp = data;
    data = other.data;
    delete temp;
}

// this just performs the forward pass operation for one Layer from the other
void NeuralLayer::update(const NeuralLayer &other) const {
    if(weights -> M != other.data -> N) {
        std::cerr << "During update operation, bias M [" << bias -> N << "] at " << bias
                  << " in object " << this << " does not match input vector size N [" << other.data -> N
                  << "] at " << other.data << '\n';
    }
    register size_t i;
    long double sum;
    if(other.bias) { // if we're not dealing with the input layer
        for(register size_t elem = 0; elem < N; ++elem) {
            sum = 0 + bias -> matrix[elem][0] -> data;
            for(i = 0; i < bias -> M; ++i) {
                sum += weights -> matrix[elem][i] -> data *
                       other.data -> matrix[i][0] -> function;
            }
            data -> matrix[elem][0] -> set(sum);
        }
    } else {
        for(register size_t elem = 0; elem < N; ++elem) {
            sum = 0 + bias -> matrix[elem][0] -> data;
            for(i = 0; i < bias -> M; ++i) {
                sum += weights -> matrix[elem][i] -> data *
                       other.data -> matrix[i][0] -> data;
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


