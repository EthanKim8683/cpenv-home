// TODO: write pratt parser
//
// the way i understand it is that there's 3 main functions:
//
// 1. parse operand
// 2. parse operator
// 3. get binding power
//
// parsing operands is for parsing stuff that can't really be divided by an
// operator, so stuff like numbers, symbols, unary operators (negation, etc.),
// or parentheses
//
// parsing operators takes an lhs operand and an operator and calls a function
// to parse the rhs operand and then combines them as necessary
//
// binding power decides when to stop parsing for a subexpression. if an
// operator's binding power is too small, that means we can't use the operator
// just yet; we need to handle the higher binding power operators first. so i
// guess in simple terms, binding power is just "what should i do first?". i
// think left/right associativity comes into play when dealing with two binding
// powers that are equal
//
// i think we can implement this nicely with a stack? or cleaner with recursion?
//
// i think operand and operator parsing are forced to have access to the parsing
// context to handle stuff with trailing tokens like parentheses or functions
//
// honestly though, i feel like trailing tokens aren't that big a deal because
// they don't provide any new information. i believe we can make these a no-op,
// at least for what a pratt parser is supposed to provide
