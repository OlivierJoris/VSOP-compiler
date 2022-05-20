; ModuleID = 'tests/codegeneration/023-isnull.vsop'
source_filename = "tests/codegeneration/023-isnull.vsop"

%MainVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i32 (%Main*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)* }
%Main = type { %MainVTable*, %Object*, %Object* }

@Main___vtable = constant %MainVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i32 (%Main*)* @Main__main }
@0 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"KO\0A\00", align 1
@2 = private unnamed_addr constant [4 x i8] c"KO\0A\00", align 1
@3 = private unnamed_addr constant [4 x i8] c"OK\0A\00", align 1

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
  %0 = call i8* @malloc(i64 192)
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
  %2 = call %Object* @Object___new()
  %3 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 1
  store %Object* %2, %Object** %3, align 8
  %4 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 2
  store %Object* null, %Object** %4, align 8
  ret %Main* %0
}

define i32 @Main__main(%Main* %0) {
entry:
  %1 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 2
  %2 = load %Object*, %Object** %1, align 8
  %3 = icmp eq %Object* %2, null
  br i1 %3, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %4 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 0
  %5 = load %MainVTable*, %MainVTable** %4, align 8
  %6 = getelementptr inbounds %MainVTable, %MainVTable* %5, i32 0, i32 0
  %7 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %6, align 8
  %8 = bitcast %Main* %0 to %Object*
  %9 = call %Object* %7(%Object* %8, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @0, i32 0, i32 0))
  br label %if_end

if_else:                                          ; preds = %entry
  %10 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 0
  %11 = load %MainVTable*, %MainVTable** %10, align 8
  %12 = getelementptr inbounds %MainVTable, %MainVTable* %11, i32 0, i32 0
  %13 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %12, align 8
  %14 = bitcast %Main* %0 to %Object*
  %15 = call %Object* %13(%Object* %14, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @1, i32 0, i32 0))
  br label %if_end

if_end:                                           ; preds = %if_else, %if_then
  %phi = phi %Object* [ %9, %if_then ], [ %15, %if_else ]
  %16 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 1
  %17 = load %Object*, %Object** %16, align 8
  %18 = icmp eq %Object* %17, null
  br i1 %18, label %if_then1, label %if_else2

if_then1:                                         ; preds = %if_end
  %19 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 0
  %20 = load %MainVTable*, %MainVTable** %19, align 8
  %21 = getelementptr inbounds %MainVTable, %MainVTable* %20, i32 0, i32 0
  %22 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %21, align 8
  %23 = bitcast %Main* %0 to %Object*
  %24 = call %Object* %22(%Object* %23, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @2, i32 0, i32 0))
  br label %if_end3

if_else2:                                         ; preds = %if_end
  %25 = getelementptr inbounds %Main, %Main* %0, i32 0, i32 0
  %26 = load %MainVTable*, %MainVTable** %25, align 8
  %27 = getelementptr inbounds %MainVTable, %MainVTable* %26, i32 0, i32 0
  %28 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %27, align 8
  %29 = bitcast %Main* %0 to %Object*
  %30 = call %Object* %28(%Object* %29, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @3, i32 0, i32 0))
  br label %if_end3

if_end3:                                          ; preds = %if_else2, %if_then1
  %phi4 = phi %Object* [ %24, %if_then1 ], [ %30, %if_else2 ]
  ret i32 0
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
