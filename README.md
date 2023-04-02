# producer-consumer
The producer produces items, 1-100, and places them in the buffer.
When the consumer is ready, it takes an item out of the buffer, and consumes it.
This process works even if the producer is faster than the consumer, and 
if the consumer is faster than the producer.

Compiling the program: clang++ -pthread producer-consumer.cpp -o producer-consumer

Running the program: ./producer-consumer

Output:
