# producer-consumer
The producer produces items, 1-100, and places them in the buffer.
When the consumer is ready, it takes an item out of the buffer, and consumes it.
This process works even if the producer is faster than the consumer, and 
if the consumer is faster than the producer.

Compiling the program: 
clang++ -pthread producer.cpp -o producer
clang++ -pthread consumer.cpp -o consumer

Running the program: ./producer & ./consumer &

Output: ![Screenshot 2023-04-06 173021](https://user-images.githubusercontent.com/15059428/230498063-88e8f3f9-26be-4710-a0d7-adc1c3938671.png)

As you can see, the producer produces a random number between 1 and 100, and puts it in the shared buffer. Then, the consumer consumes them. They are working at the same pace, as they have the same thread count, which is why the producer does not move to index 1. If it needed to it would, but the consumer does not consume the numbers quickly enough. 

If I were to increase the thread count for the producer, it would produce more numbers, but stop once the buffer is full. Here is an example of this:
![Screenshot 2023-04-06 173959](https://user-images.githubusercontent.com/15059428/230499067-f5fd4117-5d50-4ad0-9aff-dd19eadc630d.png)

As you can see, the producer will only go up to the maximum index, and the consumer is too slow to consume the numbers quickly enough, so the index stays at 1 (index started from 0, then to 1, but screenshot only shows after this).

Originally, I put both functions in one file, and did not read the instructions clearly enough. Recently, I found out that
there needs to be two, with shared memory space, which I completed.

I created a struct bufferSegment that holds each of the semaphores, the buffer, and the mutex buffer. Next, I used shmget to find a memory location that was unused, and used it as shared memory to communicate between the files. Therefore, the semaphores and mutex buffer would update with the same values, and they would be synchronized.
