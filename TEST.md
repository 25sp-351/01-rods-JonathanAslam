# TestCase 1 : properly sort the cutting lengths from most -> least valuable when given in mixed order
## Input:
- Rod Length: 20 
- Cutting Lengths: (3, 5), (4, 11), (1, 1)

## Output: 
- 5 @ 4 = 55.0
- Remainder: 0
- Value: 55


# TestCase 2 : avoid cutting rod to negative length when given too long of a input
## Input:
- Rod Length: 10 
- Cutting Lengths: (11, 1)

## Output: 
- Remainder: 10
- Value: 0


# TestCase 3 : avoid dealing with negative lengths or values
## Input: 
- Rod Length: 10
- Cutting Lengths: (-1, 1), (1, -1), (1, 1)

## Output: NOTE: this ignores the negatives and does not save them to the array of lengths_value pairs, does not stop taking inputs but continues until user enters 'ctrl + d'
- For value: (-1, 1):
    - "Cannot compute a negative, please try again"
- For value: (1, -1):
    - "Cannot compute a negative, please try again"
- For value: (1, 1):
    - Cuts Made: 10 @ 1 = 10.0
    - Remainder: 0
    - Value: 10


# TestCase 4 : cant cut perfectly
## Input:
- Rod Length: 21
- Cutting Lengths: (11, 30), (3, 6), (2, 2)

## Output:
- 1 @ 11 = 30.0
- 3 @ 3 = 18.0
- Remainder: 1
- Value: 48


