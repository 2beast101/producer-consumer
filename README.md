# producer-consumer
The producer produces items, 1-100, and places them in the buffer.
When the consumer is ready, it takes an item out of the buffer, and consumes it.
This process works even if the producer is faster than the consumer, and 
if the consumer is faster than the producer.

Compiling the program: clang++ -pthread producer-consumer.cpp -o producer-consumer

Running the program: ./producer-consumer

Output: ./producer-consumer

Produced: 83 at index: 0
Consumed: 83 at index: 1
Produced: 86 at index: 0
Consumed: 86 at index: 1
Produced: 77 at index: 0
Consumed: 77 at index: 1
Produced: 15 at index: 0
Consumed: 15 at index: 1
Produced: 93 at index: 0
Consumed: 93 at index: 1
Produced: 35 at index: 0
Consumed: 35 at index: 1
Produced: 86 at index: 0
Consumed: 86 at index: 1
Produced: 92 at index: 0
Consumed: 92 at index: 1
Produced: 49 at index: 0
Consumed: 49 at index: 1
Produced: 21 at index: 0
Consumed: 21 at index: 1
Produced: 62 at index: 0
Consumed: 62 at index: 1
Produced: 27 at index: 0
Consumed: 27 at index: 1
Produced: 90 at index: 0
Consumed: 90 at index: 1
Produced: 59 at index: 0
Consumed: 59 at index: 1