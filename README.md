Name: Newt KHN Nguyen

PennKey: newt

List of submitted source files:
1. penn-shredder.c: this is the main file.
2. handler.c: this is to handle all the signals 
3. setTimer.c: this is to count the time before alarm calls SIGALRM - used to output Bhawada... if the time is more than specified timeout

Description of code and code layout
1. penn-shredder.c: the code starts with seeing whether the user did specify any timeout or not. If not, the time is NULL. If yes, then it will take that into account. After that, it will do the work of parsing commands to avoid any leading/trailing whitespaces when the user types the command inside. Then, it will do as specified in the skeleton code on the website, call fork(), create a child process, the parent process will wait for the child process to end. For extra-credit, there is another int main() function for that, in which there will be an alarm putting inside the child process. If the child process calls the alarm, in the parent process there will be some wait signals aiming to know whether the child has called SIGALRM or not, then output the specified CATCHPHRASE statement.
2. handler.c: this is to handler all the signals, as specified in the name of the program. It will basically handle Ctrl + C and also timeout problem, but 1 has kill and the other does not have kill function.
3. setTimer.c: this is used for normal credit. It will call alarm and start.

General comments
1. This is my first time coding in C so I believe my code is still messy and unstructured in some parts. I have tried my best to make the code as easy to understand as possible.
2. I am open to any feedbacks about my code!