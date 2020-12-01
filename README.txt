compile with make compile
run with make run
clean with make clean

Alternatively you can compile then run then cat the outFile using make test

```````````````````````````````````````````````````````````````````````````````````````````````
Separate program called inFileGen.cpp which can be internally changed
to modify the number of customers and tellers that will be generated
to the inFile.txt, can be used to create an ordered inFile of any size.
```````````````````````````````````````````````````````````````````````````````````````````````

My submitted inFile contains 2 Tellers and 150 customers which has generated
an average wait time of ~270.74 seconds

The main changes made to the QueType and PriorityQueue classes were minor
and done to their printQueue functions. The only change besides that was
an additional function created in QueType called reference(int location)
where it simply returns the value stored in the queue at that reference point.

I also added a random name generator I wrote to the Customer class just for some flavor,
but there is a separate note on that within Customer.cpp


My program will automatically read an "inFile.txt" in the structure dictated
in the pdf for project 3 such as

numTellrs (some int)
numCustomers (some int)
CustomerName Arrival (some int) Service (some int)
CustomerName Arrival (some int) Service (some int)
etc...

Once it has taken the input from the inFile.txt it will begin by initalizing the
two required QueTypes for the list of unprocessed customers, which is called customers,
and the list of waiting customers, which is called waiting. As well as the single
PriorityQueue required for the customers currently being serviced, it is called servicing.

After this point it will essentially iterrate through the queue of unprocessed customers
going by arrival time of the peek customer and operate on 3 possible cases:

      1. The servicing queue is not full (tellers are available) and it will immediately
      	 place the head of the unprocessed customers queue into the servicing queue.
      2. The servicing queue is full (tellers are not available) and we will place the
      	 head of the unprocessed customers queue into the waiting queue.
      3. The current time is equal to the departure time of the head of the servicing queue
      	 (which is just that queues peekPriority()) and we will both dequeue the head
	 of the servicing queue and enqueue the head of the waiting queue.
	 At the same time the code will calculate the total wait time of the waiting queues
	 former head.

Every 5 customers that are processed based on a counter in the main file the code will print
the current list of customers being serviced and waiting.
For the waiting queue since my code only calculated the Customers wait time once they were
moved into the servicing queue originally I created the reference function to iterrate
through the queue and set an accurate wait time for how long they had waited so far.
