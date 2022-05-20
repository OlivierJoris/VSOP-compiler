; ModuleID = 'tests/codegeneration/list.vsop'
source_filename = "tests/codegeneration/list.vsop"

%ConsVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i1 (%Cons*)*, i32 (%Cons*)*, %Cons* (%Cons*, %List*, i32)*, i32 (%Cons*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)* }
%Cons = type { %ConsVTable*, i32, %List* }
%List = type { %ListVTable* }
%ListVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i1 (%List*)*, i32 (%List*)* }
%MainVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i32 (%Main*)* }
%Main = type { %MainVTable* }
%NilVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i1 (%List*)*, i32 (%List*)* }
%Nil = type { %NilVTable* }

@Cons___vtable = constant %ConsVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i1 (%Cons*)* @Cons__isNil, i32 (%Cons*)* @Cons__length, %Cons* (%Cons*, %List*, i32)* @Cons__init, i32 (%Cons*)* @Cons__head }
@List___vtable = constant %ListVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i1 (%List*)* @List__isNil, i32 (%List*)* @List__length }
@Main___vtable = constant %MainVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i32 (%Main*)* @Main__main }
@Nil___vtable = constant %NilVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i1 (%List*)* @List__isNil, i32 (%List*)* @List__length }
@0 = private unnamed_addr constant [17 x i8] c"List has length \00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

declare i8* @malloc(i64)

declare i64 @power(i32, i32)

declare %Object* @Object___new()

declare %Object* @Object___init(%Object*)

declare i1 @Object__inputBool(%Object*)

declare i32 @Object__inputInt32(%Object*)

declare i8* @Object__inputLine(%Object*)

declare %Object* @Object__print(%Object*, i8*)

declare %Object* @Object__printBool(%Object*, i1)

declare %Object* @Object__printInt32(%Object*, i32)

define %Cons* @Cons___new() {
entry:
  %0 = call dereferenceable_or_null(192) i8* @malloc(i64 192)
  %1 = bitcast i8* %0 to %List*
  %2 = call %List* @List___init(%List* %1)
  %3 = bitcast %List* %2 to %Cons*
  %4 = call %Cons* @Cons___init(%Cons* %3)
  ret %Cons* %4
}

define %Cons* @Cons___init(%Cons* %0) {
entry:
  %1 = getelementptr inbounds %Cons, %Cons* %0, i64 0, i32 0
  store %ConsVTable* @Cons___vtable, %ConsVTable** %1, align 8
  %2 = getelementptr inbounds %Cons, %Cons* %0, i64 0, i32 1
  store i32 0, i32* %2, align 4
  %3 = call %List* @List___new()
  %4 = getelementptr inbounds %Cons, %Cons* %0, i64 0, i32 2
  store %List* %3, %List** %4, align 8
  ret %Cons* %0
}

define i32 @Cons__length(%Cons* %0) {
entry:
  %1 = getelementptr inbounds %Cons, %Cons* %0, i64 0, i32 2
  %2 = load %List*, %List** %1, align 8
  %3 = getelementptr inbounds %List, %List* %2, i64 0, i32 0
  %4 = load %ListVTable*, %ListVTable** %3, align 8
  %5 = getelementptr inbounds %ListVTable, %ListVTable* %4, i64 0, i32 7
  %6 = load i32 (%List*)*, i32 (%List*)** %5, align 8
  %7 = call i32 %6(%List* %2)
  %8 = add i32 %7, 1
  ret i32 %8
}

define i1 @Cons__isNil(%Cons* %0) {
entry:
  ret i1 false
}

define i32 @Cons__head(%Cons* %0) {
entry:
  %1 = getelementptr inbounds %Cons, %Cons* %0, i64 0, i32 1
  %2 = load i32, i32* %1, align 4
  ret i32 %2
}

define %Cons* @Cons__init(%Cons* %0, %List* %1, i32 %2) {
entry:
  %3 = getelementptr inbounds %Cons, %Cons* %0, i64 0, i32 1
  store i32 %2, i32* %3, align 4
  %4 = getelementptr inbounds %Cons, %Cons* %0, i64 0, i32 2
  store %List* %1, %List** %4, align 8
  ret %Cons* %0
}

define %List* @List___new() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %Object*
  %2 = call %Object* @Object___init(%Object* %1)
  %3 = bitcast %Object* %2 to %List*
  %4 = call %List* @List___init(%List* %3)
  ret %List* %4
}

define %List* @List___init(%List* %0) {
entry:
  %1 = getelementptr inbounds %List, %List* %0, i64 0, i32 0
  store %ListVTable* @List___vtable, %ListVTable** %1, align 8
  ret %List* %0
}

define i32 @List__length(%List* %0) {
entry:
  ret i32 0
}

define i1 @List__isNil(%List* %0) {
entry:
  ret i1 true
}

define %Main* @Main___new() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %Object*
  %2 = call %Object* @Object___init(%Object* %1)
  %3 = bitcast %Object* %2 to %Main*
  %4 = call %Main* @Main___init(%Main* %3)
  ret %Main* %4
}

define %Main* @Main___init(%Main* %0) {
entry:
  %1 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  store %MainVTable* @Main___vtable, %MainVTable** %1, align 8
  ret %Main* %0
}

define i32 @Main__main(%Main* %0) {
entry:
  %1 = call %Cons* @Cons___new()
  %2 = getelementptr inbounds %Cons, %Cons* %1, i64 0, i32 0
  %3 = load %ConsVTable*, %ConsVTable** %2, align 8
  %4 = getelementptr inbounds %ConsVTable, %ConsVTable* %3, i64 0, i32 8
  %5 = load %Cons* (%Cons*, %List*, i32)*, %Cons* (%Cons*, %List*, i32)** %4, align 8
  %6 = call %Cons* @Cons___new()
  %7 = getelementptr inbounds %Cons, %Cons* %6, i64 0, i32 0
  %8 = load %ConsVTable*, %ConsVTable** %7, align 8
  %9 = getelementptr inbounds %ConsVTable, %ConsVTable* %8, i64 0, i32 8
  %10 = load %Cons* (%Cons*, %List*, i32)*, %Cons* (%Cons*, %List*, i32)** %9, align 8
  %11 = call %Cons* @Cons___new()
  %12 = getelementptr inbounds %Cons, %Cons* %11, i64 0, i32 0
  %13 = load %ConsVTable*, %ConsVTable** %12, align 8
  %14 = getelementptr inbounds %ConsVTable, %ConsVTable* %13, i64 0, i32 8
  %15 = load %Cons* (%Cons*, %List*, i32)*, %Cons* (%Cons*, %List*, i32)** %14, align 8
  %16 = call %Nil* @Nil___new()
  %17 = bitcast %Nil* %16 to %List*
  %18 = call %Cons* %15(%Cons* %11, %List* %17, i32 2)
  %19 = bitcast %Cons* %18 to %List*
  %20 = call %Cons* %10(%Cons* %6, %List* %19, i32 1)
  %21 = bitcast %Cons* %20 to %List*
  %22 = call %Cons* %5(%Cons* %1, %List* %21, i32 0)
  %23 = bitcast %Cons* %22 to %List*
  %24 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  %25 = load %MainVTable*, %MainVTable** %24, align 8
  %26 = getelementptr inbounds %MainVTable, %MainVTable* %25, i64 0, i32 0
  %27 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %26, align 8
  %28 = bitcast %Main* %0 to %Object*
  %29 = call %Object* %27(%Object* %28, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @0, i64 0, i64 0))
  %30 = load %MainVTable*, %MainVTable** %24, align 8
  %31 = getelementptr inbounds %MainVTable, %MainVTable* %30, i64 0, i32 2
  %32 = load %Object* (%Object*, i32)*, %Object* (%Object*, i32)** %31, align 8
  %33 = bitcast %Cons* %22 to %ListVTable**
  %34 = load %ListVTable*, %ListVTable** %33, align 8
  %35 = getelementptr inbounds %ListVTable, %ListVTable* %34, i64 0, i32 7
  %36 = load i32 (%List*)*, i32 (%List*)** %35, align 8
  %37 = call i32 %36(%List* %23)
  %38 = call %Object* %32(%Object* %28, i32 %37)
  %39 = load %MainVTable*, %MainVTable** %24, align 8
  %40 = getelementptr inbounds %MainVTable, %MainVTable* %39, i64 0, i32 0
  %41 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %40, align 8
  %42 = call %Object* %41(%Object* %28, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i64 0, i64 0))
  ret i32 0
}

define %Nil* @Nil___new() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %List*
  %2 = call %List* @List___init(%List* %1)
  %3 = bitcast %List* %2 to %Nil*
  %4 = call %Nil* @Nil___init(%Nil* %3)
  ret %Nil* %4
}

define %Nil* @Nil___init(%Nil* %0) {
entry:
  %1 = getelementptr inbounds %Nil, %Nil* %0, i64 0, i32 0
  store %NilVTable* @Nil___vtable, %NilVTable** %1, align 8
  ret %Nil* %0
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
