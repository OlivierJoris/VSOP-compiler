; ModuleID = 'tests/codegeneration/008-dbl-assign.vsop'
source_filename = "tests/codegeneration/008-dbl-assign.vsop"

%MainVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i32 (%Main*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)* }
%Main = type { %MainVTable*, i32 }

@Main___vtable = constant %MainVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i32 (%Main*)* @Main__main }
@0 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
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

define %Main* @Main___new() {
entry:
  %0 = call dereferenceable_or_null(128) i8* @malloc(i64 128)
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
  %2 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 1
  store i32 0, i32* %2, align 4
  ret %Main* %0
}

define i32 @Main__main(%Main* %0) {
entry:
  %1 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 1
  store i32 1984, i32* %1, align 4
  %2 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  %3 = load %MainVTable*, %MainVTable** %2, align 8
  %4 = getelementptr inbounds %MainVTable, %MainVTable* %3, i64 0, i32 2
  %5 = load %Object* (%Object*, i32)*, %Object* (%Object*, i32)** %4, align 8
  %6 = bitcast %Main* %0 to %Object*
  %7 = call %Object* %5(%Object* %6, i32 1984)
  %8 = getelementptr inbounds %Object, %Object* %7, i64 0, i32 0
  %9 = load %ObjectVTable*, %ObjectVTable** %8, align 8
  %10 = getelementptr inbounds %ObjectVTable, %ObjectVTable* %9, i64 0, i32 0
  %11 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %10, align 8
  %12 = call %Object* %11(%Object* %7, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @0, i64 0, i64 0))
  %13 = load %MainVTable*, %MainVTable** %2, align 8
  %14 = getelementptr inbounds %MainVTable, %MainVTable* %13, i64 0, i32 2
  %15 = load %Object* (%Object*, i32)*, %Object* (%Object*, i32)** %14, align 8
  %16 = load i32, i32* %1, align 4
  %17 = call %Object* %15(%Object* %6, i32 %16)
  %18 = getelementptr inbounds %Object, %Object* %17, i64 0, i32 0
  %19 = load %ObjectVTable*, %ObjectVTable** %18, align 8
  %20 = getelementptr inbounds %ObjectVTable, %ObjectVTable* %19, i64 0, i32 0
  %21 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %20, align 8
  %22 = call %Object* %21(%Object* %17, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i64 0, i64 0))
  ret i32 0
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
