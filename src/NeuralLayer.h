//
// Created by Oleg on 6/14/2018.
//

#ifndef NEURALNETWORKS_NEURALLAYER_H
#define NEURALNETWORKS_NEURALLAYER_H

#include "nn_utils.h"

class NeuralLayer {
private:
    void clean(void);

public:
    NeuralMatrix *data, *bias, *weights;

    NeuralLayer& operator=(const NeuralLayer& other);

    NeuralLayer(const size_t layer_size, const size_t previous_layer_size);

    NeuralLayer(const NeuralLayer& other);

    ~NeuralLayer(void);
};


#endif //NEURALNETWORKS_NEURALLAYER_H
