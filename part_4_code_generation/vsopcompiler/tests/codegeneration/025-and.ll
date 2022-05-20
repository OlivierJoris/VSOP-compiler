; ModuleID = 'tests/codegeneration/025-and.vsop'
source_filename = "tests/codegeneration/025-and.vsop"

%MainVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i32 (%Main*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)* }
%Main = type { %MainVTable* }

@Main___vtable = constant %MainVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i32 (%Main*)* @Main__main }
@0 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@2 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@3 = private unnamed_addr constant [4 x i8] c"KO\0A\00", align 1
@4 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@5 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@6 = private unnamed_addr constant [4 x i8] c"KO\0A\00", align 1
@7 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@8 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@9 = private unnamed_addr constant [4 x i8] c"KO\0A\00", align 1
@10 = private unnamed_addr constant [4 x i8] c"KO\0A\00", align 1
@11 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1

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
  %1 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  %2 = load %MainVTable*, %MainVTable** %1, align 8
  %3 = getelementptr inbounds %MainVTable, %MainVTable* %2, i64 0, i32 0
  %4 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %3, align 8
  %5 = bitcast %Main* %0 to %Object*
  %6 = call %Object* %4(%Object* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i64 0, i64 0))
  %7 = load %MainVTable*, %MainVTable** %1, align 8
  %8 = getelementptr inbounds %MainVTable, %MainVTable* %7, i64 0, i32 0
  %9 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %8, align 8
  %10 = call %Object* %9(%Object* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i64 0, i64 0))
  %11 = load %MainVTable*, %MainVTable** %1, align 8
  %12 = getelementptr inbounds %MainVTable, %MainVTable* %11, i64 0, i32 0
  %13 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %12, align 8
  %14 = call %Object* %13(%Object* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @2, i64 0, i64 0))
  %.pre = load %MainVTable*, %MainVTable** %1, align 8
  %.phi.trans.insert = getelementptr inbounds %MainVTable, %MainVTable* %.pre, i64 0, i32 0
  %.pre15 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %.phi.trans.insert, align 8
  %15 = getelementptr inbounds %MainVTable, %MainVTable* %.pre, i64 0, i32 0
  %16 = call %Object* %.pre15(%Object* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @4, i64 0, i64 0))
  %17 = load %MainVTable*, %MainVTable** %1, align 8
  %18 = getelementptr inbounds %MainVTable, %MainVTable* %17, i64 0, i32 0
  %19 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %18, align 8
  %20 = call %Object* %19(%Object* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @5, i64 0, i64 0))
  %21 = load %MainVTable*, %MainVTable** %1, align 8
  %22 = getelementptr inbounds %MainVTable, %MainVTable* %21, i64 0, i32 0
  %23 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %22, align 8
  %24 = call %Object* %23(%Object* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @7, i64 0, i64 0))
  %25 = load %MainVTable*, %MainVTable** %1, align 8
  %26 = getelementptr inbounds %MainVTable, %MainVTable* %25, i64 0, i32 0
  %27 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %26, align 8
  %28 = call %Object* %27(%Object* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @8, i64 0, i64 0))
  %29 = load %MainVTable*, %MainVTable** %1, align 8
  %30 = getelementptr inbounds %MainVTable, %MainVTable* %29, i64 0, i32 0
  %31 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %30, align 8
  %32 = call %Object* %31(%Object* %5, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @11, i64 0, i64 0))
  ret i32 0
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
