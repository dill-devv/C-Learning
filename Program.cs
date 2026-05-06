public static class Program
{
    public static unsafe void Main()
    {
        int x = 12; // x lives on the stack and is never touched by garbage collector
        int* p = &x;
        // assigns p as a pointer (* symbol) and & operator is used to get the memory address of x and assign it to p
        Console.WriteLine( (IntPtr)p); // writes value of p (memory address of x)
        Console.WriteLine(*p); // writes value of memory address that p is pointed at
        *p = 42; // change the value in the memory address that p points to - this is known as dereferencing the pointer

        // dereferencing means accessing the value at the memory address of the pointer

        Console.WriteLine(x); // writes new value of x, which is now 42

        int[] numbers = { 1, 12, 3, 4, 5 }; // array

        fixed (int* j = numbers) // this pins the location of variables in memory so garbage collector cannot move them around
        {
            Console.WriteLine((IntPtr)j); // writes memory address of the first element of the array
            Console.WriteLine((IntPtr)(j + 1)); // writes memory address of second element of array, this is pointer arithmetic
            Console.WriteLine(*j); // writes value of first element of array using memory location referenced by j
            Console.WriteLine(*(j + 1)); // writes value of second element of array using memory location referenced by j


            Console.WriteLine($"\nLooping through array using pointer arithmetic\n");

            for (int i = 0; i < numbers.Length; i++) // start at 0 and loop until the end of the array
            { 
                Console.WriteLine(*(j + i)); // writes value of each element in array using pointer arithmetic, j is the base address of the array and i is the offset
            };
            
            // pointer arithmetic moves the pointer by the size of the type it points to, so adding 1 to an int* moves it by 4 bytes (the size of an int)
            
        }
        Console.ReadLine(); // doesnt close terminal until I press enter
    }
}