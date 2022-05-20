; ModuleID = 'tests/codegeneration/037-return-child.vsop'
source_filename = "tests/codegeneration/037-return-child.vsop"

%ChildVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i8* (%Child*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)* }
%Child = type { %ChildVTable* }
%MainVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, %Parent* (%Main*)*, i32 (%Main*)* }
%Parent = type { %ParentVTable* }
%ParentVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i8* (%Parent*)* }
%Main = type { %MainVTable* }

@Child___vtable = constant %ChildVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i8* (%Child*)* @Child__whoAmI }
@Main___vtable = constant %MainVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, %Parent* (%Main*)* @Main__someParent, i32 (%Main*)* @Main__main }
@Parent___vtable = constant %ParentVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i8* (%Parent*)* @Parent__whoAmI }
@0 = private unnamed_addr constant [15 x i8] c"I'm a Parent.\0A\00", align 1
@1 = private unnamed_addr constant [14 x i8] c"I'm a Child.\0A\00", align 1

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

define %Child* @Child___new() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %Parent*
  %2 = call %Parent* @Parent___init(%Parent* %1)
  %3 = bitcast %Parent* %2 to %Child*
  %4 = call %Child* @Child___init(%Child* %3)
  ret %Child* %4
}

define %Child* @Child___init(%Child* %0) {
entry:
  %1 = getelementptr inbounds %Child, %Child* %0, i64 0, i32 0
  store %ChildVTable* @Child___vtable, %ChildVTable** %1, align 8
  ret %Child* %0
}

define i8* @Child__whoAmI(%Child* %0) {
entry:
  ret i8* getelementptr inbounds ([14 x i8], [14 x i8]* @1, i64 0, i64 0)
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
  %1 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  %2 = load %MainVTable*, %MainVTable** %1, align 8
  %3 = getelementptr inbounds %MainVTable, %MainVTable* %2, i64 0, i32 0
  %4 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %3, align 8
  %5 = bitcast %Main* %0 to %Object*
  %6 = getelementptr inbounds %MainVTable, %MainVTable* %2, i64 0, i32 6
  %7 = load %Parent* (%Main*)*, %Parent* (%Main*)** %6, align 8
  %8 = call %Parent* %7(%Main* %0)
  %9 = getelementptr inbounds %Parent, %Parent* %8, i64 0, i32 0
  %10 = load %ParentVTable*, %ParentVTable** %9, align 8
  %11 = getelementptr inbounds %ParentVTable, %ParentVTable* %10, i64 0, i32 6
  %12 = load i8* (%Parent*)*, i8* (%Parent*)** %11, align 8
  %13 = call i8* %12(%Parent* %8)
  %14 = call %Object* %4(%Object* %5, i8* %13)
  ret i32 0
}

define %Parent* @Main__someParent(%Main* %0) {
entry:
  %1 = call %Child* @Child___new()
  %2 = bitcast %Child* %1 to %Parent*
  ret %Parent* %2
}

define %Parent* @Parent___new() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %Object*
  %2 = call %Object* @Object___init(%Object* %1)
  %3 = bitcast %Object* %2 to %Parent*
  %4 = call %Parent* @Parent___init(%Parent* %3)
  ret %Parent* %4
}

define %Parent* @Parent___init(%Parent* %0) {
entry:
  %1 = getelementptr inbounds %Parent, %Parent* %0, i64 0, i32 0
  store %ParentVTable* @Parent___vtable, %ParentVTable** %1, align 8
  ret %Parent* %0
}

define i8* @Parent__whoAmI(%Parent* %0) {
entry:
  ret i8* getelementptr inbounds ([15 x i8], [15 x i8]* @0, i64 0, i64 0)
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
