#include "Stack.h"
/**
 * \file SortStationOther.h
 * \author Viktor Tiulpin <viktor@tiulpin.me>
 * \version 0.9
 */

/**
 * Function that creates nodes of unary and binary operations and pushes them to Operand stack.
 * \param[in] operands Operand stack
 * \param[in] operations Operation stack
 * \param[in] lastError Error code
 */
void Process(struct stack_t* operands, struct opstack_t* operations, error_t* lastError);
/**
 * Function that reads from string unary operation, number (supports scientific notation, like 1e1).
 * \param[in] string String with operation or number
 * \param[out] index Pointer to index from Convert function
 * \param[in] IsOperation Flag from Convert Function which determines what to read: number or unary operation (like sin)
 * \param[out] lastError Error code
 * \return char* Result string
 */
char* ReadOp(char* string, int* index, bool_t IsOperation, error_t* lastError);
/**
 * Function that finds in operation stack open parenthesis, for checking balancing of parentheses.
 * \param[in] operations Operation stack
 * \return bool_t TRUE or FALSE
 */
bool_t IsOPAR(struct opstack_t* operations);
/**
 * Function that finds pair for enum Op element in Binary_op elements. It's used in Process function.
 * \param[in] op Operation enum
 * \return enum Binary_op Binary operation
 */
enum Binary_op ToBinary_op(enum Op op);
/**
 * Function that finds pair for enum Op element in Unary_op elements. It's used in Process function.
 * \param[in] op Operation enum
 * \return enum Unary_op Binary operation
 */
enum Unary_op ToUnary_op(enum Op op);
/**
 * Function that defines binary operation.
 * \param[in] op Operation symbol
 * \return enum Op Binary operation
 */
enum Op DefineBinaryOp(char op);
/**
 * Function that defines unary operation.
 * \param[in] op Operation string
 * \return enum Op Unary operation
 */
enum Op DefineUnaryOp(char* op);
/**
 * Function that defines unary operation.
 * \param[in] op Operation string
 * \return enum Op Unary operation
 */
bool_t IsOperatorOrConst(char op);
/**
 * Function that defines operator priority. Pow is greater unary operations, they are greater binary and etc.
 * It's used for correct implementation of Shunting-yard algorithm.
 * \param[in] op Operation enum
 * \return int Priority number
 */
int GetPriority(enum Op op);
/**
 * Function that defines the truth of being operation unary. Calls ToBinary function, if result is invalid,then it's
 * an unary operation.
 * \param[in] op Operation enum
 * \return bool_t TRUE or FALSE
 */
bool_t IsUnaryOp(enum Op op);