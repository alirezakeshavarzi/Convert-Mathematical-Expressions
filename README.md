# Convert Mathematical Expressions

A C++ project for converting and evaluating mathematical expressions using **stack-based algorithms**.

The project supports three common mathematical expression notations:

* **Infix** — `1+2*3`
* **Prefix** — `+1*23`
* **Postfix** — `123*+`

It also provides functionality for validating expressions and evaluating prefix/postfix expressions.

## Features

* Convert **Infix → Postfix**
* Convert **Infix → Prefix**
* Convert **Prefix → Infix**
* Convert **Prefix → Postfix**
* Convert **Postfix → Infix**
* Convert **Postfix → Prefix**
* Evaluate **Prefix** expressions
* Evaluate **Postfix** expressions
* Basic mathematical expression validation
* Stack-based implementation using C++

## Expression Notations

### Infix

Infix notation is the standard notation commonly used in mathematics, where operators are written between operands.

```text
11 + 22 * 33
```

### Prefix

In prefix notation, the operator is placed before its operands.

```text
+ 11 * 22 33
```

The equivalent expression without spaces is:

```text
+11*2233
```

### Postfix

In postfix notation, the operator is placed after its operands.

```text
11 22 33 * +
```

The equivalent expression without spaces is:

```text
112233*+
```

## How It Works

The project uses a **stack** as the main data structure for expression conversion and evaluation.

For example, when converting an infix expression to postfix, operators are temporarily stored in a stack according to their precedence.

Operator precedence in the implementation is:

| Operator | Precedence |
| -------- | ---------- |
| `+` `-`  | 2          |
| `*` `/`  | 4          |
| `^`      | 5          |

Parentheses are also handled during infix-to-prefix and infix-to-postfix conversion.

## Supported Operations

The following operators are supported:

```text
+
-
*
/
^
```

The project also supports parentheses for infix expressions:

```text
( )
```

## Example

For the following infix expression:

```text
11+22*33
```

The corresponding postfix expression is:

```text
112233*+
```

And the corresponding prefix expression is:

```text
+11*2233
```

## Evaluation

Prefix and postfix expressions can be evaluated using a stack.

For example:

```text
Postfix:
23*4+
```

The evaluation process produces:

```text
10
```

Similarly, prefix expressions can be evaluated by scanning the expression from right to left.

## Project Structure

The main implementation is contained in the C++ source file and includes functions for:

```text
Stack operations
├── push()
├── pop()
├── stack_empty()
└── stack_full()

Expression conversion
├── Infix_to_postfix()
├── Infix_to_prefix()
├── prefix_to_infix()
├── prefix_to_postfix()
├── postfix_to_infix()
└── postfix_to_prefix()

Expression evaluation
├── postfix_eval()
└── prefix_eval()

Expression validation
└── Expression_validation()
```

## Requirements

* A C++ compiler supporting standard C++
* Standard C++ library

For example:

* GCC
* MinGW
* Clang
* Visual Studio

## How to Run

Clone the repository:

```bash
git clone https://github.com/alirezakeshavarzi/Convert-Mathematical-Expressions.git
```

Navigate to the project directory:

```bash
cd Convert-Mathematical-Expressions
```

Compile the source code:

```bash
g++ main.cpp -o expression_converter
```

Run the program:

### Linux / macOS

```bash
./expression_converter
```

### Windows

```bash
expression_converter.exe
```

## Learning Objectives

This project was developed to practice and demonstrate:

* Stack data structures
* Operator precedence
* Expression parsing
* Infix, prefix, and postfix notation
* Algorithm implementation in C++
* Basic expression evaluation
* Problem solving using data structures

## Limitations

The current implementation is primarily designed for learning and practicing expression conversion algorithms. Some limitations include:

* Expressions are currently handled mainly as single-digit operands during conversion and evaluation.
* The stack has a fixed size in the current implementation.
* Input validation is basic and does not cover every possible invalid expression.
* Unary operators such as unary minus are not fully supported.
* Division is performed using integer arithmetic during evaluation.

These limitations can be addressed in future versions.

# Convert Mathematical Expressions

A C++ project for converting and evaluating mathematical expressions using **stack-based algorithms**.

The project supports three common mathematical expression notations:

* **Infix** — `1+2*3`
* **Prefix** — `+1*23`
* **Postfix** — `123*+`

It also provides functionality for validating expressions and evaluating prefix/postfix expressions.

## Features

* Convert **Infix → Postfix**
* Convert **Infix → Prefix**
* Convert **Prefix → Infix**
* Convert **Prefix → Postfix**
* Convert **Postfix → Infix**
* Convert **Postfix → Prefix**
* Evaluate **Prefix** expressions
* Evaluate **Postfix** expressions
* Basic mathematical expression validation
* Stack-based implementation using C++

## Expression Notations

### Infix

Infix notation is the standard notation commonly used in mathematics, where operators are written between operands.

```text
11 + 22 * 33
```

### Prefix

In prefix notation, the operator is placed before its operands.

```text
+ 11 * 22 33
```

The equivalent expression without spaces is:

```text
+11*2233
```

### Postfix

In postfix notation, the operator is placed after its operands.

```text
11 22 33 * +
```

The equivalent expression without spaces is:

```text
112233*+
```

## How It Works

The project uses a **stack** as the main data structure for expression conversion and evaluation.

For example, when converting an infix expression to postfix, operators are temporarily stored in a stack according to their precedence.

Operator precedence in the implementation is:

| Operator | Precedence |
| -------- | ---------- |
| `+` `-`  | 2          |
| `*` `/`  | 4          |
| `^`      | 5          |

Parentheses are also handled during infix-to-prefix and infix-to-postfix conversion.

## Supported Operations

The following operators are supported:

```text
+
-
*
/
^
```

The project also supports parentheses for infix expressions:

```text
( )
```

## Example

For the following infix expression:

```text
11+22*33
```

The corresponding postfix expression is:

```text
112233*+
```

And the corresponding prefix expression is:

```text
+11*2233
```

## Evaluation

Prefix and postfix expressions can be evaluated using a stack.

For example:

```text
Postfix:
23*4+
```

The evaluation process produces:

```text
10
```

Similarly, prefix expressions can be evaluated by scanning the expression from right to left.

## Project Structure

The main implementation is contained in the C++ source file and includes functions for:

```text
Stack operations
├── push()
├── pop()
├── stack_empty()
└── stack_full()

Expression conversion
├── Infix_to_postfix()
├── Infix_to_prefix()
├── prefix_to_infix()
├── prefix_to_postfix()
├── postfix_to_infix()
└── postfix_to_prefix()

Expression evaluation
├── postfix_eval()
└── prefix_eval()

Expression validation
└── Expression_validation()
```

## Requirements

* A C++ compiler supporting standard C++
* Standard C++ library

For example:

* GCC
* MinGW
* Clang
* Visual Studio

## How to Run

Clone the repository:

```bash
git clone https://github.com/alirezakeshavarzi/Convert-Mathematical-Expressions.git
```

Navigate to the project directory:

```bash
cd Convert-Mathematical-Expressions
```

Compile the source code:

```bash
g++ main.cpp -o expression_converter
```

Run the program:

### Linux / macOS

```bash
./expression_converter
```

### Windows

```bash
expression_converter.exe
```

## Learning Objectives

This project was developed to practice and demonstrate:

* Stack data structures
* Operator precedence
* Expression parsing
* Infix, prefix, and postfix notation
* Algorithm implementation in C++
* Basic expression evaluation
* Problem solving using data structures

## Limitations

The current implementation is primarily designed for learning and practicing expression conversion algorithms. Some limitations include:

* Expressions are currently handled mainly as single-digit operands during conversion and evaluation.
* The stack has a fixed size in the current implementation.
* Input validation is basic and does not cover every possible invalid expression.
* Unary operators such as unary minus are not fully supported.
* Division is performed using integer arithmetic during evaluation.

These limitations can be addressed in future versions.
