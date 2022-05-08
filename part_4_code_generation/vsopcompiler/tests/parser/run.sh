make -j
echo
echo \* Testing 01_class.vsop \*
./vsopc -p tests/parser/01_class.vsop
echo
echo \* Testing 02_class_extended.vsop \*
./vsopc -p tests/parser/02_class_extended.vsop
echo
echo \* Testing 03_class_field.vsop \*
./vsopc -p tests/parser/03_class_field.vsop
echo
echo \* Testing 04_class_field_default_value.vsop \*
./vsopc -p tests/parser/04_class_field_default_value.vsop
echo
echo \* Testing 05_class_method.vsop \*
./vsopc -p tests/parser/05_class_method.vsop
echo
echo \* Testing 06_class_method_with_args.vsop \*
./vsopc -p tests/parser/06_class_method_with_args.vsop
echo
echo \* Testing 07_while.vsop \*
./vsopc -p tests/parser/07_while.vsop
echo
echo \* Testing 08_let.vsop \*
./vsopc -p tests/parser/08_let.vsop
echo
echo \* Testing 09_let_assign.vsop \*
./vsopc -p tests/parser/09_let_assign.vsop
echo
echo \* Testing 10_if_then.vsop \*
./vsopc -p tests/parser/10_if_then.vsop
echo
echo \* Testing 11_if_then.vsop \*
./vsopc -p tests/parser/11_if_then.vsop
echo
echo \* Testing 12_if_then_else.vsop \*
./vsopc -p tests/parser/12_if_then_else.vsop
