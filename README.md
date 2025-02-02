# IMPLEMENTATION OF A NN USING THE MNIST DATASET IN ORDER TO RECOGNIZE DIGITS

## The net is composed of 4 layers:

- **1 input layer**  
  - size `784` (28×28 pixels flattened into a vector)  
  - Each pixel is normalized to `[0,1]` by dividing by `255`  

- **1 hidden layer composed of 10 neurons**  
  - **Weights:** `W1` (shape: `10 × 784`), randomly initialized  
  - **Biases:** `b1` (shape: `10 × 1`), randomly initialized  
  - **Activation Function:** **ReLU** (Rectified Linear Unit)  

- **1 output layer of 10 neurons**  
  - **Size:** `OUTPUT_SIZE = 10` (corresponding to 10 digit classes: `0-9`)  
  - **Weights:** `W2` (shape: `10 × 10`), randomly initialized  
  - **Biases:** `b2` (shape: `10 × 1`), randomly initialized  
  - **Activation Function:** **Softmax**, which converts logits into probabilities  

![Acc plot](acc.png)  

I know we got some overfitting but the accuracy of the model wasn't the scope of the exercice.
