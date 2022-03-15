make -j
echo
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
