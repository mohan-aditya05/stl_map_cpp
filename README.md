# stl_map_cpp

***The work done here may only be used as reference material. The work here is not to be submitted as your own, with or without edits.***

## How to run

```
$ make <target>
$ ./target
```

Target can be
- test
- test-kec
- morseex
- test-scaling
- minimal

## Performance Test Statistics

************************************
	Ascending insert for cs440::Map<int, int>	
************************************

Inserting 1,000 elements in ascending order took 1.21634 milliseconds<br>
Inserting 10,000 elements in ascending order took 13.4328 milliseconds<br>
Inserting 100,000 elements in ascending order took 141.419 milliseconds<br>
Inserting 1,000,000 elements in ascending order took 1,479.79 milliseconds<br>
Inserting 10,000,000 elements in ascending order took 24,978.9 milliseconds<br>


************************************
	Ascending insert for cs440::StdMapWrapper<int, int>	
************************************

Inserting 1,000 elements in ascending order took 0.590342 milliseconds<br>
Inserting 10,000 elements in ascending order took 7.28986 milliseconds<br>
Inserting 100,000 elements in ascending order took 95.0749 milliseconds<br>
Inserting 1,000,000 elements in ascending order took 1,099.48 milliseconds<br>
Inserting 10,000,000 elements in ascending order took 13,200.9 milliseconds<br>


************************************
	Descending insert for cs440::Map<int, int>	
************************************

Inserting 1,000 elements in descending order took 1.18551 milliseconds<br>
Inserting 10,000 elements in descending order took 12.2197 milliseconds<br>
Inserting 100,000 elements in descending order took 137.312 milliseconds<br>
Inserting 1,000,000 elements in descending order took 1,381.51 milliseconds<br>
Inserting 10,000,000 elements in descending order took 13,638.1 milliseconds<br>


************************************
	Descending insert for cs440::StdMapWrapper<int, int>	
************************************

Inserting 1,000 elements in descending order took 0.573759 milliseconds<br>
Inserting 10,000 elements in descending order took 7.22485 milliseconds<br>
Inserting 100,000 elements in descending order took 93.6032 milliseconds<br>
Inserting 1,000,000 elements in descending order took 1,102.14 milliseconds<br>
Inserting 10,000,000 elements in descending order took 14,100.4 milliseconds<br>

************************************
	Delete test for cs440::Map<int, int>	
************************************

deleting 10000 elements from a map of size 10000 took 10.2543 milliseconds<br>
deleting 10000 elements from a map of size 100000 took 21.3431 milliseconds<br>
deleting 10000 elements from a map of size 1000000 took 29.6481 milliseconds<br>
deleting 10000 elements from a map of size 10000000 took 48.8621 milliseconds<br>


************************************
	Delete test for cs440::StdMapWrapper<int, int>	
************************************

deleting 10000 elements from a map of size 10000 took 7.2801 milliseconds<br>
deleting 10000 elements from a map of size 100000 took 12.312 milliseconds<br>
deleting 10000 elements from a map of size 1000000 took 22.1875 milliseconds<br>
deleting 10000 elements from a map of size 10000000 took 28.363 milliseconds<br>

************************************
	Find test for cs440::Map<int, int>	
************************************

Finding 10000 elements from a map of size 10,000 took 21.6723 milliseconds<br>
Finding 10000 elements from a map of size 100,000 took 42.1596 milliseconds<br>
Finding 10000 elements from a map of size 1,000,000 took 54.9679 milliseconds<br>
Finding 10000 elements from a map of size 10,000,000 took 74.4059 milliseconds<br>

************************************
	Find test for cs440::StdMapWrapper<int, int>	
************************************

Finding 10000 elements from a map of size 10,000 took 12.647 milliseconds<br>
Finding 10000 elements from a map of size 100,000 took 20.0189 milliseconds<br>
Finding 10000 elements from a map of size 1,000,000 took 28.5584 milliseconds<br>
Finding 10000 elements from a map of size 10,000,000 took 31.563 milliseconds<br>


************************************
	Iteration test for cs440::Map<int, int>	
************************************

Iterating across 10,000 elements in a map of size 10,000 took 1.23543 milliseconds time per iteration was 123.543 nanoseconds<br>
Iterating across 20,000 elements in a map of size 20,000 took 2.38023 milliseconds time per iteration was 119.011 nanoseconds<br>
Iterating across 40,000 elements in a map of size 40,000 took 4.9495 milliseconds time per iteration was 123.738 nanoseconds<br>
Iterating across 80,000 elements in a map of size 80,000 took 9.2812 milliseconds time per iteration was 116.015 nanoseconds<br>
Iterating across 160,000 elements in a map of size 160,000 took 36.6472 milliseconds time per iteration was 229.045 nanoseconds<br>
Iterating across 320,000 elements in a map of size 320,000 took 77.9462 milliseconds time per iteration was 243.582 nanoseconds<br>
Iterating across 640,000 elements in a map of size 640,000 took 144.319 milliseconds time per iteration was 225.498 nanoseconds<br>
Iterating across 1,280,000 elements in a map of size 1,280,000 took 243.878 milliseconds time per iteration was 190.53 nanoseconds<br>
Iterating across 2,560,000 elements in a map of size 2,560,000 took 382.571 milliseconds time per iteration was 149.442 nanoseconds<br>
Iterating across 5,120,000 elements in a map of size 5,120,000 took 680.323 milliseconds time per iteration was 132.876 nanoseconds<br>


************************************
	Iteration test for cs440::StdMapWrapper<int, int>	
************************************

Iterating across 10,000 elements in a map of size 10,000 took 0.910808 milliseconds time per iteration was 91.0808 nanoseconds<br>
Iterating across 20,000 elements in a map of size 20,000 took 1.80209 milliseconds time per iteration was 90.1045 nanoseconds<br>
Iterating across 40,000 elements in a map of size 40,000 took 3.65427 milliseconds time per iteration was 91.3568 nanoseconds<br>
Iterating across 80,000 elements in a map of size 80,000 took 7.44324 milliseconds time per iteration was 93.0404 nanoseconds<br>
Iterating across 160,000 elements in a map of size 160,000 took 16.8862 milliseconds time per iteration was 105.539 nanoseconds<br>
Iterating across 320,000 elements in a map of size 320,000 took 52.92 milliseconds time per iteration was 165.375 nanoseconds<br>
Iterating across 640,000 elements in a map of size 640,000 took 101.814 milliseconds time per iteration was 159.085 nanoseconds<br>
Iterating across 1,280,000 elements in a map of size 1,280,000 took 195.398 milliseconds time per iteration was 152.655 nanoseconds<br>
Iterating across 5,120,000 elements in a map of size 5,120,000 took 681.165 milliseconds time per iteration was 133.04 nanoseconds<br>

************************************
	Copy test for cs440::Map<int, int>	
************************************

Copy construction of a map of size 10,000 took 13.0654 milliseconds<br>
Copy construction of a map of size 100,000 took 153.538 milliseconds<br>
Copy construction of a map of size 1,000,000 took 1,761.55 milliseconds<br>
Copy construction of a map of size 10,000,000 took 26,122.9 milliseconds<br>


************************************
	Copy test for cs440::StdMapWrapper<int, int>	
************************************

Copy construction of a map of size 10,000 took 1.77954 milliseconds<br>
Copy construction of a map of size 100,000 took 34.3416 milliseconds<br>
Copy construction of a map of size 1,000,000 took 344.16 milliseconds<br>
Copy construction of a map of size 10,000,000 took 2,544.16 milliseconds<br>
