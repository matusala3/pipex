#include "libft/libft.h"
#include <fcntl.h>

void test_ft_printf(void)
{
    ft_printf("=== Testing ft_printf ===\n");
    
    // Test basic string and character
    ft_printf("String test: %s\n", "Hello, World!");
    ft_printf("Character test: %c\n", 'A');
    
    // Test integers
    ft_printf("Integer test: %d\n", 42);
    ft_printf("Negative integer: %d\n", -123);
    
    // Test unsigned
    ft_printf("Unsigned test: %u\n", 4294967295U);
    
    // Test hexadecimal
    ft_printf("Hex lowercase: %x\n", 255);
    ft_printf("Hex uppercase: %X\n", 255);
    
    // Test pointer
    void *ptr = (void *)0x7fff1234;
    ft_printf("Pointer test: %p\n", ptr);
    ft_printf("NULL pointer: %p\n", NULL);
    
    // Test percent
    ft_printf("Percent test: %%\n");
    
    // Combined test
    ft_printf("Combined: %s has %d items, hex: %x, char: %c\n", 
              "Array", 10, 160, '!');
    
    ft_printf("=== ft_printf tests completed ===\n\n");
}

void test_get_next_line(void)
{
    ft_printf("=== Testing get_next_line ===\n");
    
    // Create a test file
    int fd_write = open("test_input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_write == -1)
    {
        ft_printf("Error: Could not create test file\n");
        return;
    }
    
    // Write test content
    write(fd_write, "Line 1: First line\n", 19);
    write(fd_write, "Line 2: Second line\n", 20);
    write(fd_write, "Line 3: Third line\n", 19);
    write(fd_write, "Line 4: Last line without newline", 34);
    close(fd_write);
    
    // Test reading with get_next_line
    int fd_read = open("test_input.txt", O_RDONLY);
    if (fd_read == -1)
    {
        ft_printf("Error: Could not open test file for reading\n");
        return;
    }
    
    char *line;
    int line_count = 1;
    
    ft_printf("Reading file line by line:\n");
    while ((line = get_next_line(fd_read)) != NULL)
    {
        ft_printf("Line %d: %s", line_count, line);
        if (line[ft_strlen(line) - 1] != '\n')
            ft_printf("\n");
        free(line);
        line_count++;
    }
    
    close(fd_read);
    
    // Test with empty file
    fd_write = open("empty_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    close(fd_write);
    
    fd_read = open("empty_test.txt", O_RDONLY);
    line = get_next_line(fd_read);
    if (line == NULL)
        ft_printf("Empty file test: ✅ Correctly returned NULL\n");
    else
    {
        ft_printf("Empty file test: ❌ Should have returned NULL\n");
        free(line);
    }
    close(fd_read);
    
    // Cleanup
    unlink("test_input.txt");
    unlink("empty_test.txt");
    
    ft_printf("=== get_next_line tests completed ===\n\n");
}

void test_integration(void)
{
    ft_printf("=== Testing Integration ===\n");
    
    // Test using ft_printf to display get_next_line results
    int fd = open("integration_test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    write(fd, "Integration test line 1\n", 24);
    write(fd, "Integration test line 2\n", 24);
    close(fd);
    
    fd = open("integration_test.txt", O_RDONLY);
    char *line;
    
    ft_printf("Using ft_printf to display get_next_line results:\n");
    while ((line = get_next_line(fd)) != NULL)
    {
        ft_printf("→ %s", line);
        free(line);
    }
    close(fd);
    unlink("integration_test.txt");
    
    ft_printf("=== Integration test completed ===\n\n");
}

int main(void)
{
    ft_printf("🧪 Testing Integrated libft with ft_printf and get_next_line\n");
    ft_printf("============================================================\n\n");
    
    // Test ft_printf functionality
    test_ft_printf();
    
    // Test get_next_line functionality  
    test_get_next_line();
    
    // Test integration of both
    test_integration();
    
    ft_printf("✅ All tests completed successfully!\n");
    ft_printf("Your integrated libft is working perfectly! 🎉\n");
    
    return (0);
} 