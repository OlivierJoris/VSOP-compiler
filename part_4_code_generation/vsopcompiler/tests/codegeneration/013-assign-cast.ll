; ModuleID = 'tests/codegeneration/013-assign-cast.vsop'
source_filename = "tests/codegeneration/013-assign-cast.vsop"

%MainVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i32 (%Main*)*, %Object* (%Main*, %Object*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)* }
%Main = type { %MainVTable*, %Object* }

@Main___vtable = constant %MainVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i32 (%Main*)* @Main__main, %Object* (%Main*, %Object*)* @Main__useObject }
@0 = private unnamed_addr constant [55 x i8] c"This argument looks like it is a valid Object object.\0A\00", align 1

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
  %2 = call %Object* @Object___new()
  %3 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 1
  store %Object* %2, %Object** %3, align 8
  ret %Main* %0
}

define i32 @Main__main(%Main* %0) {
entry:
  %1 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 1
  %2 = bitcast %Object** %1 to %Main**
  store %Main* %0, %Main** %2, align 8
  %3 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  %4 = load %MainVTable*, %MainVTable** %3, align 8
  %5 = getelementptr inbounds %MainVTable, %MainVTable* %4, i64 0, i32 7
  %6 = load %Object* (%Main*, %Object*)*, %Object* (%Main*, %Object*)** %5, align 8
  %.cast = bitcast %Main* %0 to %Object*
  %7 = call %Object* %6(%Main* %0, %Object* %.cast)
  ret i32 0
}

define %Object* @Main__useObject(%Main* %0, %Object* %1) {
entry:
  %2 = getelementptr inbounds %Object, %Object* %1, i64 0, i32 0
  %3 = load %ObjectVTable*, %ObjectVTable** %2, align 8
  %4 = getelementptr inbounds %ObjectVTable, %ObjectVTable* %3, i64 0, i32 0
  %5 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %4, align 8
  %6 = call %Object* %5(%Object* %1, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @0, i64 0, i64 0))
  ret %Object* %6
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
