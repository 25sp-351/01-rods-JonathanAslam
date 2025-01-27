# TestCase 1 : properly sort the cutting lengths from most -> least valuable when given in mixed order
## Input:
- Rod Length: 20 
- Cutting Lengths: (3, 5), (4, 11), (1, 1)

## Output: 
- Cuts made: 5 @ 4 = 55.0
- Remainder: 0
- Total Value: 55


# TestCase 2 : avoid cutting rod to negative length when given too long of a input
## Input:
- Rod Length: 10 
- Cutting Lengths: (11, 1)

## Output: 
- Cuts Made: 0 @ 0 = 0.0
- Remainder: 10
- Total Value: 0


# TestCase 3 : avoid dealing with negative lengths or values
## Input: 
- Rod Length: 10
- Cutting Lengths: (-1, 1), (1, -1), (1, 1)

## Output:
- For value: (-1, 1):
    - "Please enter a valid, non-negative length and value"
- For value: (1, -1):
    - "Please enter a valid, non-negative length and value"
- For value: (1, 1):
    - Cuts Made: 10 @ 1 = 10.0
    - Remainder: 0
    - Total Value: 10.0


# TestCase 4 : cant cut perfectly
## Input:
- Rod Length: 21
- Cutting Lengths: (11, 30), (3, 6), (2, 2)

## Output:
- Cuts Made: 1 @ 11 = 30.0
- Cuts Made: 3 @ 3 = 18.0
- Remainder: 1
- Total Value: 48.0


