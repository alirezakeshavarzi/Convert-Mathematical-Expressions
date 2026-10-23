// ---------------------------------------------------------------------------
// Unit tests for the Infix/Prefix/Postfix Expression Converter & Evaluator
//
// Setup:  put this file next to expression_converter.cpp (your source file).
// Build:  compile ONLY this file (it #includes your source):
//     g++ -std=c++17 test_expression_converter.cpp -o run_tests && ./run_tests
//     (MSVC: cl /std:c++17 /EHsc test_expression_converter.cpp)
//
// No external framework is needed. Two kinds of checks:
//   CHECK_EQ(actual, expected)       -> must pass; a failure is a real regression
//   XFAIL_EQ(actual, expected, why)  -> a KNOWN BUG: expected to fail today.
//        When you fix the bug it turns into XPASS: change it to CHECK_EQ.
// ---------------------------------------------------------------------------

// Rename your main() so it does not clash with the test runner's main().
#define main expression_converter_main
#include "expression_converter.cpp"
#undef main

#include <sstream>

// ----------------------------- tiny test harness ---------------------------
static int g_pass = 0, g_fail = 0, g_xfail = 0, g_xpass = 0;
static const char* g_test = "";

// Silences cout while a function under test prints its own messages.
struct Quiet {
    streambuf* old;
    ostringstream sink;
    Quiet() : old(cout.rdbuf(sink.rdbuf())) {}
    ~Quiet() { cout.rdbuf(old); }
};

#define CHECK_EQ(actual, expected)                                            \
    do {                                                                      \
        const string a_ = (actual);                                           \
        const string e_ = (expected);                                         \
        if (a_ == e_) { ++g_pass; }                                           \
        else {                                                                \
            ++g_fail;                                                         \
            cout << "  FAIL  [" << g_test << "] line " << __LINE__            \
                 << "\n        expected: \"" << e_ << "\"\n        actual:   \"" \
                 << a_ << "\"\n";                                             \
        }                                                                     \
    } while (0)

#define XFAIL_EQ(actual, expected, why)                                       \
    do {                                                                      \
        const string a_ = (actual);                                           \
        const string e_ = (expected);                                         \
        if (a_ == e_) {                                                       \
            ++g_xpass;                                                        \
            cout << "  XPASS [" << g_test << "] line " << __LINE__            \
                 << " - bug seems fixed, switch to CHECK_EQ\n";               \
        } else {                                                              \
            ++g_xfail;                                                        \
            cout << "  XFAIL [" << g_test << "] line " << __LINE__ << ": "     \
                 << why << "\n        expected: \"" << e_                     \
                 << "\"  actual: \"" << a_ << "\"\n";                         \
        }                                                                     \
    } while (0)

#define RUN(fn) do { g_test = #fn; fn(); } while (0)

// ------------------------------- helpers -----------------------------------
// Every function under test relies on the global `n` and on a fresh stack,
// so each helper creates a new stack and sets `n` the way main() does.
static string to_postfix(const string& e) {
    n = (int)e.size(); stack st; string ans;
    Infix_to_postfix(ans, st, e);
    return ans;
}
static string to_prefix(const string& e) {
    stack st; string ans;
    Infix_to_prefix(ans, st, e);
    return ans;
}
static string pre_to_in(const string& e)  { stack st; string a; prefix_to_infix(a, st, e);   return a; }
static string pre_to_post(const string& e){ stack st; string a; prefix_to_postfix(a, st, e); return a; }
static string post_to_in(const string& e) { stack st; string a; postfix_to_infix(a, st, e);  return a; }
static string post_to_pre(const string& e){ stack st; string a; postfix_to_prefix(a, st, e); return a; }
static string eval_post(const string& e)  { Quiet q; stack st; string a; postfix_eval(a, st, e); return a; }
static string eval_pre(const string& e)   { Quiet q; stack st; string a; prefix_eval(a, st, e);  return a; }

// ================================ STACK ======================================
void test_stack_basics() {
    n = 6;                                   // capacity rule: full when top == n/2
    stack st;
    CHECK_EQ(to_string(stack_empty(st)), "1");
    push(st, "a");
    CHECK_EQ(to_string(stack_empty(st)), "0");
    push(st, "b");
    CHECK_EQ(pop(st), "b");                  // LIFO order
    CHECK_EQ(pop(st), "a");
    CHECK_EQ(to_string(stack_empty(st)), "1");
}

void test_stack_full_refuses_push() {
    n = 6;
    stack st;
    Quiet q;                                 // push() prints "Stack is full!"
    for (int i = 0; i < 4; ++i) push(st, to_string(i));
    CHECK_EQ(to_string(stack_full(st)), "1");
    push(st, "overflow");                    // must be rejected, not stored
    CHECK_EQ(to_string(st.top), "3");
    CHECK_EQ(pop(st), "3");
}

void test_stack_pop_empty_sentinel() {
    // Documents current behaviour: an error message is returned as normal data.
    stack st;
    XFAIL_EQ(pop(st) == "Stack is empty." ? string("returns error text")
                                         : string("signals error"),
             "signals error",
             "pop() on an empty stack returns the string \"Stack is empty.\" "
             "which later code treats as a value (should throw / return a status)");
}

// ============================ INFIX -> POSTFIX ================================
void test_infix_to_postfix_basic() {
    CHECK_EQ(to_postfix("1+2"),   "12+");
    CHECK_EQ(to_postfix("7"),     "7");
    CHECK_EQ(to_postfix("1+2-3"), "12+3-");
}

void test_infix_to_postfix_precedence() {
    CHECK_EQ(to_postfix("1+2*3"),   "123*+");
    CHECK_EQ(to_postfix("1*2+3"),   "12*3+");
    CHECK_EQ(to_postfix("1+2*3-4"), "123*+4-");
    CHECK_EQ(to_postfix("2^3*4"),   "23^4*");
}

void test_infix_to_postfix_left_associativity() {
    CHECK_EQ(to_postfix("1-2-3"), "12-3-");
    CHECK_EQ(to_postfix("8/4/2"), "84/2/");
}

void test_infix_to_postfix_parentheses() {
    CHECK_EQ(to_postfix("(1+2)*3"),     "12+3*");
    CHECK_EQ(to_postfix("2*(3+4)"),     "234+*");
    CHECK_EQ(to_postfix("((1+2)*(3+4))"), "12+34+*");
}

void test_infix_to_postfix_right_assoc_power() {
    XFAIL_EQ(to_postfix("2^3^2"), "232^^",
             "'^' is treated as left-associative (pops on equal precedence)");
}

void test_infix_to_postfix_multi_digit() {
    XFAIL_EQ(to_postfix("12+34"), "12 34 +",
             "only single-digit operands: each digit char is its own operand, "
             "no token separator");
}

// ============================ INFIX -> PREFIX =================================
void test_infix_to_prefix() {
    XFAIL_EQ(to_prefix("1+2"),   "+12",
             "result of reverse(ans) is discarded, so ans is left un-reversed");
    XFAIL_EQ(to_prefix("1+2*3"), "+1*23",
             "same: reverse(ans) result is discarded");
    XFAIL_EQ(to_prefix("1-2-3"), "--123",
             "right-to-left scan must NOT pop on equal precedence "
             "(left-associativity is wrong for prefix)");
    // Parentheses in prefix are not tested on purpose: in the right-to-left
    // scan ')' is processed first and the code reads st.s[st.top] with
    // top == -1 (out-of-bounds, undefined behaviour).
}

// ============================ PREFIX <-> POSTFIX ==============================
void test_prefix_to_postfix() {
    CHECK_EQ(pre_to_post("+12"),    "12+");
    CHECK_EQ(pre_to_post("+1*23"),  "123*+");
    CHECK_EQ(pre_to_post("*+123"),  "12+3*");
    CHECK_EQ(pre_to_post("-1-23"),  "123--");   // 1-(2-3)
}

void test_postfix_to_prefix() {
    CHECK_EQ(post_to_pre("12+"),    "+12");
    CHECK_EQ(post_to_pre("123*+"),  "+1*23");
    CHECK_EQ(post_to_pre("12+3*"),  "*+123");
    CHECK_EQ(post_to_pre("123--"),  "-1-23");
}

void test_prefix_postfix_round_trip() {
    const char* exprs[] = { "+12", "+1*23", "*+123", "-1-23", "-+123", "/84" };
    for (const char* p : exprs) {
        CHECK_EQ(post_to_pre(pre_to_post(p)), p);
    }
}

// ============================ -> INFIX (no parentheses) =======================
void test_to_infix_simple() {
    CHECK_EQ(pre_to_in("+12"),   "1+2");
    CHECK_EQ(pre_to_in("+1*23"), "1+2*3");
    CHECK_EQ(post_to_in("12+"),  "1+2");
    CHECK_EQ(post_to_in("12-"),  "1-2");
    CHECK_EQ(post_to_in("123*+"), "1+2*3");
}

void test_to_infix_needs_parentheses() {
    XFAIL_EQ(pre_to_in("*+123"),  "(1+2)*3",
             "parentheses are never emitted, so the infix string changes meaning");
    XFAIL_EQ(post_to_in("12+3*"), "(1+2)*3",
             "parentheses are never emitted (and the whole string is reversed)");
    XFAIL_EQ(post_to_in("123--"), "1-(2-3)",
             "parentheses are never emitted");
}

// ================================ EVALUATION ==================================
void test_postfix_eval_commutative() {
    CHECK_EQ(eval_post("12+"),    "3");
    CHECK_EQ(eval_post("34*5+"),  "17");
    CHECK_EQ(eval_post("123*+"),  "7");
}

void test_postfix_eval_non_commutative() {
    XFAIL_EQ(eval_post("52-"), "3",
             "operands popped in the wrong order: computes 2-5 = -3");
    XFAIL_EQ(eval_post("82/"), "4",
             "operands popped in the wrong order: computes 2/8 = 0");
    XFAIL_EQ(eval_post("23^"), "8",
             "wrong operand order (computes 3^2) and pow() result is "
             "converted with to_string(double)");
}

void test_prefix_eval() {
    CHECK_EQ(eval_pre("+12"),   "3");
    CHECK_EQ(eval_pre("-52"),   "3");
    CHECK_EQ(eval_pre("/82"),   "4");
    CHECK_EQ(eval_pre("+1*23"), "7");
    CHECK_EQ(eval_pre("*+123"), "9");
}

void test_prefix_eval_power_formatting() {
    XFAIL_EQ(eval_pre("^23"), "8",
             "result of pow() goes through to_string(double) -> \"8.000000\"");
}

void test_eval_pre_and_post_agree() {
    // The same expression in both notations must give the same value.
    CHECK_EQ(eval_pre("+1*23"), eval_post("123*+"));
    CHECK_EQ(eval_pre("*+123"), eval_post("12+3*"));
}

// ================================ VALIDATION ==================================
void test_validation_classifies_notation() {
    CHECK_EQ(Expression_validation("+12"),       "prefix");
    CHECK_EQ(Expression_validation("12+"),       "postfix");
    CHECK_EQ(Expression_validation("11+22*33"),  "infix");
    CHECK_EQ(Expression_validation("1+2+3"),     "infix");
}

void test_validation_rejects_bad_input() {
    CHECK_EQ(Expression_validation("1++2"), "nothing!...");
}

void test_validation_known_gaps() {
    XFAIL_EQ(Expression_validation("1+2"), "infix",
             "loop bound i < n-2 skips the only operator in 3-char expressions");
    XFAIL_EQ(Expression_validation("(1+2)*3"), "infix",
             "expressions starting with '(' are rejected");
    XFAIL_EQ(Expression_validation("1+2+"), "nothing!...",
             "a trailing operator is classified as valid postfix");
}

// ================================== MAIN ======================================
int main() {
    RUN(test_stack_basics);
    RUN(test_stack_full_refuses_push);
    RUN(test_stack_pop_empty_sentinel);

    RUN(test_infix_to_postfix_basic);
    RUN(test_infix_to_postfix_precedence);
    RUN(test_infix_to_postfix_left_associativity);
    RUN(test_infix_to_postfix_parentheses);
    RUN(test_infix_to_postfix_right_assoc_power);
    RUN(test_infix_to_postfix_multi_digit);

    RUN(test_infix_to_prefix);

    RUN(test_prefix_to_postfix);
    RUN(test_postfix_to_prefix);
    RUN(test_prefix_postfix_round_trip);

    RUN(test_to_infix_simple);
    RUN(test_to_infix_needs_parentheses);

    RUN(test_postfix_eval_commutative);
    RUN(test_postfix_eval_non_commutative);
    RUN(test_prefix_eval);
    RUN(test_prefix_eval_power_formatting);
    RUN(test_eval_pre_and_post_agree);

    RUN(test_validation_classifies_notation);
    RUN(test_validation_rejects_bad_input);
    RUN(test_validation_known_gaps);

    cout << "\n==== " << g_pass << " passed, " << g_fail << " FAILED, "
         << g_xfail << " known bugs (xfail), " << g_xpass << " xpass ====\n";
    return g_fail == 0 ? 0 : 1;
}