#include 
#include 
#include 

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

#define F_MINUS 1
#define F_PLUS  2
#define F_ZERO  4
#define F_HASH  8
#define F_SPACE 16

#define S_LONG  2
#define S_SHORT 1

struct fmt {
    char fmt;
    int (*fn)(va_list, char[], int, int, int, int);
};

void print_buffer(char buffer[], int *buff_ind);

int my_printf(const char *format, ...)
{
    if (format == NULL)
        return -1;

    va_list args;
    va_start(args, format);

    char buffer[BUFF_SIZE];
    int buff_ind = 0;
    int printed_chars = 0;

    for (int i = 0; format[i] != '\0'; i++) {
        if (format[i] == '%') {
            // Handle format specifiers here
            // For demonstration, let's consider only %d specifier
            i++;  // Move past '%'
            if (format[i] == 'd') {
                int num = va_arg(args, int);
                int len = snprintf(buffer + buff_ind, BUFF_SIZE - buff_ind, "%d", num);
                if (len >= 0)
                    buff_ind += len;
                
                printed_chars += len;
            }
            // Add other format specifiers as needed
        } else {
            buffer[buff_ind++] = format[i];
            if (buff_ind == BUFF_SIZE)
                print_buffer(buffer, &buff_ind);
            
            printed_chars++;
        }
    }

    // Flush remaining buffer
    print_buffer(buffer, &buff_ind);

    va_end(args);

    return printed_chars;
}

int main() {
    my_printf("Hello, %s! The answer is %d.\n", "User", 42);
    return 0;
}

void print_buffer(char buffer[], int *buff_ind) {
    // Implement the logic to print the buffer or write it to a file
    // Here, I'm just printing it to the console
    write(1, buffer, *buff_ind);
    *buff_ind = 0;  // Reset buffer index
}
