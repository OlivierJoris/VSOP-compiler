# Generally:
- Scoping rules
- Typing rules
- Evaluation rules
- Cannot use a type that is not defined

# Classes:
- Cannot be redefined
- Fields and methods
- Cannot have multiple fields or methods with the same name. But can have 1 field and 1 method with the same name
- Types of fields, formal arguments, and return types must be given explicitly

# New:
- Create object as java
- Space for each field
- Pointer to a table of its methods
- Initialise fields and methods table pointer

# Inheritance:
- Inherits all fields and methods of parent class
- Inheritance is transitive
- Illegal to redefine a field of a parent class in child class
- Can override methods (keep same return type, and args' types). Take precedence
- Single inheritance
- No inheritance cycles
- Static types >< dynamic types

# Dispatch:
- Dot operator: call method of object through object-oriented dispatch
- Depends on dynamic type
- Cannot dispatch to an invalid method (related to inheritance)

# Fiels:
- If initialiser, executed when a new object is created
- Type of initialiser must match with type of field
- Cannot use self or other fields/methods in initialiser
- If no initialiser, default-initialised
- null as in Java, C,C++
- Fields are initialised in the order of inheritance starting from Object down to the object class
- Fiels are like protected in java. Only in class and children

# Methods:
- All methods are public
- Zero or more parameters. Cannot have multiple parameters with the same name
- Parameters take precedence over fields
- self refer to object itself (like Java)
- Return type must match what was declared

# Object class:
- Default parent class of a class (same as Java). Common ancestor.
- All classes are members of a tree rooted at Object

# Main class:
- Program must have a Main class
- Main class must contain a main method with no args and return int32
- Object of class Main is instantiated and the method main is called
- Return value of main method is used as the program exit code

# Expressions - literals:
- Evaluate to its value
- bool = true or false
- int32 = 32-bit signed int
- string = bytes followed by NUL character \0
- unit = () same as void in C

# Expressions - identifiers:
- Name of local var, param, self, fields are expressions
- Binding refers to the innermost lexical scope that contains a declaration for that identifier or the field
- A field can thus be hidden by a formal parameter or local variable, a formal parameter can be hidden by a local variable, and a local variable can be hidden by another local variable declaration with the same name within its scope
- self - bound to the current object in every method and cannot be hidden
- self is reserved keyword (syntax error)
- Cannot use a not defined identifier

# Expressions - assignments:
- <id> <- <expr>: first evaluates expr than assign value to identifier id
- Type of <expr> must be equivalent to type of id
- Value of assignment is value of expr

# Expressions - dispatch:
- If static type of <expr_0> is P, check that P has or inherits a method <id> with n params
<expr_0>.<id>(<expr1>, …, <exprn>)
- <expr0> is evaluated first
- Then, args are evaluated

# Expressions - conditionals:
- if <cond> then <expr_t> else <expr_e>
- <cond> must be of type bool
- Types of <expr_t> and <expr_e> must agree

# Expressions - loops:
- while <cond> do <expr>
- <cond> must be of type bool
- <expr> can be any type
- Type of loop is unit

# Expressions - blocks:
- Expressions are evaluated in order of appearance inside the block
- Type and value of block are those of last expression inside it

# Expressions - lets:
- let <id> : <type> [<- <init_expr>] in <body_expr>
- If <init_expr> it is first evaluated. Type must conform to <type>
- If no <init_expr>, <id> is bound to default initialiser of <type>
- Value of let is value of body
- Type of let is the type of the body
- Scope of binding is limited to <body_expr>

# Expressions - arithmetic, logic, and comparison operations:
- All binary operator except and first evaluate left-hand side then right-hand side
- < and <= are only for int32 and return bool
- Arithmetic operations return int32 (no floating point division)
- = only on any 2 values with the same primitive type. Return true or false. First evaluate left-hand side. If true, evaluate right-hand side. RHS must be valid expr.
- Between 2 objects, true if same memory addr. Else, false
- Logical operators act on bool and return bool