# java parser
A simple implementation of a java parser.
A top-down parser that uses a one-token lookahead is called an LL(1) parser. 
The first L indicates that the input is read from left to right. 
The second L says that it produces a left-to-right derivation.
Usually the parse() method receives some string as input, "extracts" 
the necessary information from it and converts it into an object of the calling class. 
For example, it received a string and returned the date that was "hiding" in this string.
