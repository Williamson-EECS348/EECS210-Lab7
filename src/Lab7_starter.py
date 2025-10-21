# Name:
# KUID:
# Lab session:
# Lab #7
# Description:
#
# Collaborators:
# Outside sources:

#This function is similar to Lab 3, but now it will keep running until the user inputs a square matrix
def get_square_matrix(ints=False):
    """ 
    Takes a square matrix of numbers from the user. Each row can be 
    separated by commas and/or spaces. Automatically ends after the last row.

    If ints=False, the function returns a matrix of strings. 
    If ints=True, they will be cast to int instead
    """
    print("Enter your matrix:")
    matrix = []

    x = input()
    #If blank line, try again
    if not x.strip():
        return get_square_matrix(ints=ints)

    items = x.replace(",", " ").split()
    length = len(items)
    matrix = []

    #Save the first row
    if not ints:
        matrix.append(items)
    else:
        try:
            row = [int(entry) for entry in items]
            matrix.append(items)
        except ValueError:
            print("Error: all entries must be numbers! Try again:")
            #If first row is bad, try again
            return get_square_matrix(ints=ints)

    #Get the rest of the rows
    while True:
        x = input()
        items = x.replace(",", " ").split()
        if len(items) != length:
            print("Error: row lengths are mismatched! Try again:")
            continue  # re-try the line
        if not ints:
            matrix.append(items)
        else:
            try:
                row = [int(entry) for entry in items]
                matrix.append(row)
            except ValueError:
                print("Error: all entries must be numbers! Try again:")
                continue  # re-try the line
        #Check if matrix has been completed (is square)
        if len(matrix) == length:
            return matrix

#Helper function to print a 2-D matrix
def print_matrix(m):
    for row in m:
        for item in row:
            print(item, end=" ")
        print()

def main():
    M_R = get_square_matrix(ints=True)
    print("Got: ")
    print_matrix(M_R)

if __name__ == "__main__":
    main()
