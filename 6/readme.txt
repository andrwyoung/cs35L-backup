There were many issues when doing this homework

I thought it would be simple to just implement the different threads in the main() function. 
Guess it wasn't that simple because apparently pthread_create needs a function inputted
so I had to take the whole loop part out of the main() function

Then I didn't realize I needed to move the scaled_colors out of the function too
eventually I realized I needed to take it out and I just created a struct to hold colors
and then printed them out later on in the main() function

but when testing it, it kept on printing out newlines
so took me a while to realize I needed to get rid of the print("\n");

This homework took me so much time...
But yes. There is a very clear improvement depending on how many threads there are
You can see this when looking at the times
As the threads double, the program speed pretty much doubles as well

with 1 thread, it was about 40 seconds
with 2 threads, it was about 20 seconds
with 4 threads, it was about 10 seconds
with 8 threads, it was about 5 seconds
