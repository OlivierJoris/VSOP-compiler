; ModuleID = 'tests/codegeneration/021-nested-ifs.vsop'
source_filename = "tests/codegeneration/021-nested-ifs.vsop"

%MainVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)*, i32 (%Main*)*, void (%Main*)* }
%Object = type { %ObjectVTable* }
%ObjectVTable = type { %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i8* (%Object*)*, i1 (%Object*)*, i32 (%Object*)* }
%Main = type { %MainVTable*, i32 }

@Main___vtable = constant %MainVTable { %Object* (%Object*, i8*)* @Object__print, %Object* (%Object*, i1)* @Object__printBool, %Object* (%Object*, i32)* @Object__printInt32, i8* (%Object*)* @Object__inputLine, i1 (%Object*)* @Object__inputBool, i32 (%Object*)* @Object__inputInt32, i32 (%Main*)* @Main__main, void (%Main*)* @Main__guessN }
@0 = private unnamed_addr constant [5 x i8] c"n = \00", align 1
@1 = private unnamed_addr constant [12 x i8] c", guess is \00", align 1
@2 = private unnamed_addr constant [6 x i8] c"n < 0\00", align 1
@3 = private unnamed_addr constant [8 x i8] c"n > 100\00", align 1
@4 = private unnamed_addr constant [6 x i8] c"n = 0\00", align 1
@5 = private unnamed_addr constant [6 x i8] c"n = 1\00", align 1
@6 = private unnamed_addr constant [6 x i8] c"n = 2\00", align 1
@7 = private unnamed_addr constant [6 x i8] c"n = 3\00", align 1
@8 = private unnamed_addr constant [6 x i8] c"n = 4\00", align 1
@9 = private unnamed_addr constant [6 x i8] c"n = 5\00", align 1
@10 = private unnamed_addr constant [6 x i8] c"n = 6\00", align 1
@11 = private unnamed_addr constant [6 x i8] c"n = 7\00", align 1
@12 = private unnamed_addr constant [6 x i8] c"n = 8\00", align 1
@13 = private unnamed_addr constant [6 x i8] c"n = 9\00", align 1
@14 = private unnamed_addr constant [7 x i8] c"n = 10\00", align 1
@15 = private unnamed_addr constant [7 x i8] c"n = 11\00", align 1
@16 = private unnamed_addr constant [13 x i8] c"12 <= n < 25\00", align 1
@17 = private unnamed_addr constant [13 x i8] c"25 <= n < 50\00", align 1
@18 = private unnamed_addr constant [15 x i8] c"50 <= n <= 100\00", align 1
@19 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

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
  %1 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  %2 = load %MainVTable*, %MainVTable** %1, align 8
  %3 = getelementptr inbounds %MainVTable, %MainVTable* %2, i64 0, i32 7
  %4 = load void (%Main*)*, void (%Main*)** %3, align 8
  call void %4(%Main* %0)
  %5 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 1
  store i32 1, i32* %5, align 4
  %6 = load %MainVTable*, %MainVTable** %1, align 8
  %7 = getelementptr inbounds %MainVTable, %MainVTable* %6, i64 0, i32 7
  %8 = load void (%Main*)*, void (%Main*)** %7, align 8
  call void %8(%Main* %0)
  store i32 2, i32* %5, align 4
  %9 = load %MainVTable*, %MainVTable** %1, align 8
  %10 = getelementptr inbounds %MainVTable, %MainVTable* %9, i64 0, i32 7
  %11 = load void (%Main*)*, void (%Main*)** %10, align 8
  call void %11(%Main* %0)
  store i32 4, i32* %5, align 4
  %12 = load %MainVTable*, %MainVTable** %1, align 8
  %13 = getelementptr inbounds %MainVTable, %MainVTable* %12, i64 0, i32 7
  %14 = load void (%Main*)*, void (%Main*)** %13, align 8
  call void %14(%Main* %0)
  store i32 8, i32* %5, align 4
  %15 = load %MainVTable*, %MainVTable** %1, align 8
  %16 = getelementptr inbounds %MainVTable, %MainVTable* %15, i64 0, i32 7
  %17 = load void (%Main*)*, void (%Main*)** %16, align 8
  call void %17(%Main* %0)
  store i32 16, i32* %5, align 4
  %18 = load %MainVTable*, %MainVTable** %1, align 8
  %19 = getelementptr inbounds %MainVTable, %MainVTable* %18, i64 0, i32 7
  %20 = load void (%Main*)*, void (%Main*)** %19, align 8
  call void %20(%Main* %0)
  store i32 32, i32* %5, align 4
  %21 = load %MainVTable*, %MainVTable** %1, align 8
  %22 = getelementptr inbounds %MainVTable, %MainVTable* %21, i64 0, i32 7
  %23 = load void (%Main*)*, void (%Main*)** %22, align 8
  call void %23(%Main* %0)
  store i32 64, i32* %5, align 4
  %24 = load %MainVTable*, %MainVTable** %1, align 8
  %25 = getelementptr inbounds %MainVTable, %MainVTable* %24, i64 0, i32 7
  %26 = load void (%Main*)*, void (%Main*)** %25, align 8
  call void %26(%Main* %0)
  store i32 128, i32* %5, align 4
  %27 = load %MainVTable*, %MainVTable** %1, align 8
  %28 = getelementptr inbounds %MainVTable, %MainVTable* %27, i64 0, i32 7
  %29 = load void (%Main*)*, void (%Main*)** %28, align 8
  call void %29(%Main* %0)
  ret i32 0
}

define void @Main__guessN(%Main* %0) {
entry:
  %1 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  %2 = load %MainVTable*, %MainVTable** %1, align 8
  %3 = getelementptr inbounds %MainVTable, %MainVTable* %2, i64 0, i32 0
  %4 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %3, align 8
  %5 = bitcast %Main* %0 to %Object*
  %6 = call %Object* %4(%Object* %5, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i64 0, i64 0))
  %7 = getelementptr inbounds %Object, %Object* %6, i64 0, i32 0
  %8 = load %ObjectVTable*, %ObjectVTable** %7, align 8
  %9 = getelementptr inbounds %ObjectVTable, %ObjectVTable* %8, i64 0, i32 2
  %10 = load %Object* (%Object*, i32)*, %Object* (%Object*, i32)** %9, align 8
  %11 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 1
  %12 = load i32, i32* %11, align 4
  %13 = call %Object* %10(%Object* %6, i32 %12)
  %14 = getelementptr inbounds %Object, %Object* %13, i64 0, i32 0
  %15 = load %ObjectVTable*, %ObjectVTable** %14, align 8
  %16 = getelementptr inbounds %ObjectVTable, %ObjectVTable* %15, i64 0, i32 0
  %17 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %16, align 8
  %18 = call %Object* %17(%Object* %13, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @1, i64 0, i64 0))
  %19 = load i32, i32* %11, align 4
  %20 = icmp slt i32 %19, 0
  br i1 %20, label %if_then, label %if_else

if_then:                                          ; preds = %entry
  %21 = load %MainVTable*, %MainVTable** %1, align 8
  %22 = getelementptr inbounds %MainVTable, %MainVTable* %21, i64 0, i32 0
  %23 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %22, align 8
  %24 = call %Object* %23(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @2, i64 0, i64 0))
  br label %if_end59

if_else:                                          ; preds = %entry
  %25 = icmp sgt i32 %19, 100
  br i1 %25, label %if_then1, label %if_else2

if_then1:                                         ; preds = %if_else
  %26 = load %MainVTable*, %MainVTable** %1, align 8
  %27 = getelementptr inbounds %MainVTable, %MainVTable* %26, i64 0, i32 0
  %28 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %27, align 8
  %29 = call %Object* %28(%Object* %5, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @3, i64 0, i64 0))
  br label %if_end59

if_else2:                                         ; preds = %if_else
  %30 = icmp slt i32 %19, 50
  br i1 %30, label %if_then3, label %if_else54

if_then3:                                         ; preds = %if_else2
  %31 = icmp slt i32 %19, 25
  br i1 %31, label %if_then4, label %if_else51

if_then4:                                         ; preds = %if_then3
  %32 = icmp slt i32 %19, 12
  br i1 %32, label %if_then5, label %if_else48

if_then5:                                         ; preds = %if_then4
  %33 = icmp slt i32 %19, 6
  br i1 %33, label %if_then6, label %if_else25

if_then6:                                         ; preds = %if_then5
  %34 = icmp slt i32 %19, 3
  br i1 %34, label %if_then7, label %if_else14

if_then7:                                         ; preds = %if_then6
  %35 = icmp slt i32 %19, 2
  br i1 %35, label %if_then8, label %if_else11

if_then8:                                         ; preds = %if_then7
  %36 = icmp slt i32 %19, 1
  %37 = load %MainVTable*, %MainVTable** %1, align 8
  %38 = getelementptr inbounds %MainVTable, %MainVTable* %37, i64 0, i32 0
  %39 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %38, align 8
  br i1 %36, label %if_then9, label %if_else10

if_then9:                                         ; preds = %if_then8
  %40 = call %Object* %39(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @4, i64 0, i64 0))
  br label %if_end59

if_else10:                                        ; preds = %if_then8
  %41 = call %Object* %39(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @5, i64 0, i64 0))
  br label %if_end59

if_else11:                                        ; preds = %if_then7
  %42 = load %MainVTable*, %MainVTable** %1, align 8
  %43 = getelementptr inbounds %MainVTable, %MainVTable* %42, i64 0, i32 0
  %44 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %43, align 8
  %45 = call %Object* %44(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @6, i64 0, i64 0))
  br label %if_end59

if_else14:                                        ; preds = %if_then6
  %46 = icmp slt i32 %19, 4
  br i1 %46, label %if_then15, label %if_else16

if_then15:                                        ; preds = %if_else14
  %47 = load %MainVTable*, %MainVTable** %1, align 8
  %48 = getelementptr inbounds %MainVTable, %MainVTable* %47, i64 0, i32 0
  %49 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %48, align 8
  %50 = call %Object* %49(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @7, i64 0, i64 0))
  br label %if_end59

if_else16:                                        ; preds = %if_else14
  %51 = icmp slt i32 %19, 5
  %52 = load %MainVTable*, %MainVTable** %1, align 8
  %53 = getelementptr inbounds %MainVTable, %MainVTable* %52, i64 0, i32 0
  %54 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %53, align 8
  br i1 %51, label %if_then17, label %if_else18

if_then17:                                        ; preds = %if_else16
  %55 = call %Object* %54(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @8, i64 0, i64 0))
  br label %if_end59

if_else18:                                        ; preds = %if_else16
  %56 = call %Object* %54(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @9, i64 0, i64 0))
  br label %if_end59

if_else25:                                        ; preds = %if_then5
  %57 = icmp slt i32 %19, 9
  br i1 %57, label %if_then26, label %if_else35

if_then26:                                        ; preds = %if_else25
  %58 = icmp slt i32 %19, 7
  br i1 %58, label %if_then27, label %if_else28

if_then27:                                        ; preds = %if_then26
  %59 = load %MainVTable*, %MainVTable** %1, align 8
  %60 = getelementptr inbounds %MainVTable, %MainVTable* %59, i64 0, i32 0
  %61 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %60, align 8
  %62 = call %Object* %61(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @10, i64 0, i64 0))
  br label %if_end59

if_else28:                                        ; preds = %if_then26
  %63 = icmp slt i32 %19, 8
  %64 = load %MainVTable*, %MainVTable** %1, align 8
  %65 = getelementptr inbounds %MainVTable, %MainVTable* %64, i64 0, i32 0
  %66 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %65, align 8
  br i1 %63, label %if_then29, label %if_else30

if_then29:                                        ; preds = %if_else28
  %67 = call %Object* %66(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @11, i64 0, i64 0))
  br label %if_end59

if_else30:                                        ; preds = %if_else28
  %68 = call %Object* %66(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @12, i64 0, i64 0))
  br label %if_end59

if_else35:                                        ; preds = %if_else25
  %69 = icmp slt i32 %19, 10
  br i1 %69, label %if_then36, label %if_else37

if_then36:                                        ; preds = %if_else35
  %70 = load %MainVTable*, %MainVTable** %1, align 8
  %71 = getelementptr inbounds %MainVTable, %MainVTable* %70, i64 0, i32 0
  %72 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %71, align 8
  %73 = call %Object* %72(%Object* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @13, i64 0, i64 0))
  br label %if_end59

if_else37:                                        ; preds = %if_else35
  %74 = icmp slt i32 %19, 11
  %75 = load %MainVTable*, %MainVTable** %1, align 8
  %76 = getelementptr inbounds %MainVTable, %MainVTable* %75, i64 0, i32 0
  %77 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %76, align 8
  br i1 %74, label %if_then38, label %if_else39

if_then38:                                        ; preds = %if_else37
  %78 = call %Object* %77(%Object* %5, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @14, i64 0, i64 0))
  br label %if_end59

if_else39:                                        ; preds = %if_else37
  %79 = call %Object* %77(%Object* %5, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @15, i64 0, i64 0))
  br label %if_end59

if_else48:                                        ; preds = %if_then4
  %80 = load %MainVTable*, %MainVTable** %1, align 8
  %81 = getelementptr inbounds %MainVTable, %MainVTable* %80, i64 0, i32 0
  %82 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %81, align 8
  %83 = call %Object* %82(%Object* %5, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @16, i64 0, i64 0))
  br label %if_end59

if_else51:                                        ; preds = %if_then3
  %84 = load %MainVTable*, %MainVTable** %1, align 8
  %85 = getelementptr inbounds %MainVTable, %MainVTable* %84, i64 0, i32 0
  %86 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %85, align 8
  %87 = call %Object* %86(%Object* %5, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @17, i64 0, i64 0))
  br label %if_end59

if_else54:                                        ; preds = %if_else2
  %88 = load %MainVTable*, %MainVTable** %1, align 8
  %89 = getelementptr inbounds %MainVTable, %MainVTable* %88, i64 0, i32 0
  %90 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %89, align 8
  %91 = call %Object* %90(%Object* %5, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @18, i64 0, i64 0))
  br label %if_end59

if_end59:                                         ; preds = %if_then1, %if_else51, %if_then15, %if_else18, %if_then17, %if_else11, %if_else10, %if_then9, %if_then36, %if_else39, %if_then38, %if_then27, %if_else30, %if_then29, %if_else48, %if_else54, %if_then
  %92 = load %MainVTable*, %MainVTable** %1, align 8
  %93 = getelementptr inbounds %MainVTable, %MainVTable* %92, i64 0, i32 0
  %94 = load %Object* (%Object*, i8*)*, %Object* (%Object*, i8*)** %93, align 8
  %95 = call %Object* %94(%Object* %5, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @19, i64 0, i64 0))
  ret void
}

define i32 @main() {
entry:
  %0 = call %Main* @Main___new()
  %1 = call i32 @Main__main(%Main* %0)
  ret i32 %1
}
