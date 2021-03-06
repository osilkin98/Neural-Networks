//
// Created by Oleg on 6/29/2018.
//

#ifndef NEURALNETWORKS_MATRIX_OPERATORS_H
#define NEURALNETWORKS_MATRIX_OPERATORS_H

#include "namespaces.h"
#include "neural_matrix.h"
#include <string>

/*
 * we have to use this namespace for operators until I can figure out a better way to manage all of these
 * operations in an intuitive manner
 * */

namespace neural_networks::utilities::matrix_operators {

    // this is for the user to specify what mode they want to copy the NeuralMatrix object with
    enum Mode { data = 0, function = 1, derivative = 2};

    Matrix<long double> *subtract(const Matrix<long double> *first, const NeuralMatrix *second);

    Matrix<long double> *subtract(
            const NeuralMatrix *first,
            const Matrix<long double> *second);

    Matrix<long double> *hadamard_product(const Matrix<long double> *first, const NeuralMatrix *other);

    Matrix<long double> *hadamard_product(const NeuralMatrix *first, const Matrix<long double> *other);

    Matrix<long double> *multiply(const Matrix<long double> *first, const NeuralMatrix *other);

    Matrix<long double> *multiply(const NeuralMatrix *first, const Matrix<long double> *other);

    Matrix<long double> *add(const Matrix<long double> *first, const NeuralMatrix *other);

    Matrix<long double> *add(const NeuralMatrix *first, const Matrix<long double> *other);

    /* the field parameter specifies which field to grab from the Neuron objects */
    Matrix<long double> *create(const NeuralMatrix* other, Mode mod = data);

    // to create randomized matrices
    Matrix<long double> *create_randomized_matrix(size_t N, size_t M = 1,
            long double mean = 0.0, long double stddev = 2.0);

};

#endif //NEURALNETWORKS_MATRIX_OPERATORS_H
