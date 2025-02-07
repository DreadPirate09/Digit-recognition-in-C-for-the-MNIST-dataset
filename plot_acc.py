import matplotlib.pyplot as plt

logs_file = "logs_train"
logs = open(logs_file).read()

train_accuracies = []
test_accuracies = []

# Extract training and testing accuracy
for line in logs.split('\n'):
    if 'The accuracy train is' in line:
        train_acc = float(line.split('The accuracy train is : ')[1].split()[0])
        
        train_accuracies.append(train_acc)
    if 'The accuracy test is' in line:
        test_acc = float(line.split('The accuracy test is : ')[1].split()[0])
        test_accuracies.append(test_acc)

print(train_accuracies);

epochs = range(len(train_accuracies))

plt.plot(epochs, train_accuracies, label='Train Accuracy')
plt.plot(epochs, test_accuracies, label='Test Accuracy')
plt.xlabel('Epochs')
plt.ylabel('Accuracy')
plt.legend()
plt.title('Training and Testing Accuracy Over Epochs')
plt.show()
