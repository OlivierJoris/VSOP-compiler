; ModuleID = 'tests/codegeneration/simple.vsop'
source_filename = "tests/codegeneration/simple.vsop"

%MainVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i32 (%Main*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)* }
%Main = type { %MainVTable* }
%MyClassVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)* }
%MyClass = type { %MyClassVTable*, i1 }

@Main___vtable = constant %MainVTable { i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i8* (%Object*)* @Object__inputLine, %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i32 (%Main*)* @Main__main }
@MyClass___vtable = constant %MyClassVTable { i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i8* (%Object*)* @Object__inputLine, %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32 }

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
  ret i32 0
}

define %MyClass* @MyClass___new() {
entry:
  %0 = call dereferenceable_or_null(128) i8* @malloc(i64 128)
  %1 = bitcast i8* %0 to %Object*
  %2 = call %Object* @Object___init(%Object* %1)
  %3 = bitcast %Object* %2 to %MyClass*
  %4 = call %MyClass* @MyClass___init(%MyClass* %3)
  ret %MyClass* %4
}

define %MyClass* @MyClass___init(%MyClass* %0) {
entry:
  %1 = getelementptr inbounds %MyClass, %MyClass* %0, i64 0, i32 0
  store %MyClassVTable* @MyClass___vtable, %MyClassVTable** %1, align 8
  %2 = getelementptr inbounds %MyClass, %MyClass* %0, i64 0, i32 1
  store i1 false, i1* %2, align 1
  ret %MyClass* %0
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
