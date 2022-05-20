; ModuleID = 'tests/006-new.vsop'
source_filename = "tests/006-new.vsop"

%MainVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i32 (%Main*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)* }
%Main = type { %MainVTable* }

@Main___vtable = constant %MainVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i32 (%Main*)* @Main__main }
@0 = private unnamed_addr constant [17 x i8] c"Hello, it's me.\0A\00", align 1

declare %Object* @Object___new()

declare %Object* @Object___init(%Object*)

declare %Object* @Object__print(%Object*, i8*)

declare %Object* @Object__printBool(%Object*, i1)

declare %Object* @Object__printInt32(%Object*, i32)

declare i8* @Object__inputLine(%Object*)

declare i1 @Object__inputBool(%Object*)

declare i32 @Object__inputInt32(%Object*)

declare i8* @malloc(i64)

declare i64 @power(i32, i32)

define %Main* @Main___new() {
entry:
  %0 = call i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %Object*
  %2 = call %Object* @Object___init(%Object* %1)
  %3 = bitcast %Object* %2 to %Main*
  %4 = call %Main* @Main___init(%Main* %3)
  ret %Main* %4
}

define %Main* @Main___init(%Main* %0) {
entry:
  %1 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 0
  store %MainVTable* @Main___vtable, %MainVTable** %1, align 8
  ret %Main* %0
}

define i32 @Main__main(%Main* %0) {
entry:
  %1 = call %Object* @Object___new()
  %2 = getelementptr inbounds %Object, %Object* %1, i32 0, i32 0
  %3 = load %ObjectVTable*, %ObjectVTable** %2, align 8
  %4 = getelementptr inbounds %ObjectVTable, %ObjectVTable* %3, i32 0, i32 0
  %5 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %4, align 8
  %6 = call %Object* %5(%Object* %1, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @0, i32 0, i32 0))
  ret i32 0
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
