# producer-consumer
The producer produces items, 1-100, and places them in the buffer.
When the consumer is ready, it takes an item out of the buffer, and consumes it.
This process works even if the producer is faster than the consumer, and 
if the consumer is faster than the producer.

Compiling the program: clang++ -pthread producer-consumer.cpp -o producer-consumer

Running the program: ./producer-consumer

Output: ![Screenshot 2023-04-06 173021](https://user-images.githubusercontent.com/15059428/230498063-88e8f3f9-26be-4710-a0d7-adc1c3938671.png)



Originally, I put both functions in one file, and did not read the instructions clearly enough. Recently, I found out that
there needs to be two, with shared memory space, which I attempted. 

You can see my progress through producer.cpp and consumer.cpp, although producer-consumer.cpp works as intended, just without a shared memory between two different files. 
There is, however shared memory between the processes in one file.

