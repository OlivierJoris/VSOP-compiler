; ModuleID = 'tests/codegeneration/classes.vsop'
source_filename = "tests/codegeneration/classes.vsop"

%struct.ChildVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)* }
%Object = type { %struct.ObjectVTable* }
%struct.ObjectVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)* }
%struct.GrandParentVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)* }
%struct.MainVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)*, i32 (%Main*)* }
%Main = type { %struct.MainVTable* }
%struct.MyClassVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)* }
%struct.ParentVTable = type { i1 (%Object*)*, i32 (%Object*)*, i8* (%Object*)*, %Object* (%Object*, i8*)*, %Object* (%Object*, i1)*, %Object* (%Object*, i32)* }
%Child = type { %struct.ChildVTable* }
%Parent = type { %struct.ParentVTable* }
%GrandParent = type { %struct.GrandParentVTable* }
%MyClass = type { %struct.MyClassVTable*, %GrandParent* }

@Child_vtable = constant %struct.ChildVTable { i1 (%Object*)* @inputBool_Object, i32 (%Object*)* @inputInt32_Object, i8* (%Object*)* @inputLine_Object, %Object* (%Object*, i8*)* @print_Object, %Object* (%Object*, i1)* @printBool_Object, %Object* (%Object*, i32)* @printInt32_Object }
@GrandParent_vtable = constant %struct.GrandParentVTable { i1 (%Object*)* @inputBool_Object, i32 (%Object*)* @inputInt32_Object, i8* (%Object*)* @inputLine_Object, %Object* (%Object*, i8*)* @print_Object, %Object* (%Object*, i1)* @printBool_Object, %Object* (%Object*, i32)* @printInt32_Object }
@Main_vtable = constant %struct.MainVTable { i1 (%Object*)* @inputBool_Object, i32 (%Object*)* @inputInt32_Object, i8* (%Object*)* @inputLine_Object, %Object* (%Object*, i8*)* @print_Object, %Object* (%Object*, i1)* @printBool_Object, %Object* (%Object*, i32)* @printInt32_Object, i32 (%Main*)* @main_Main }
@MyClass_vtable = constant %struct.MyClassVTable { i1 (%Object*)* @inputBool_Object, i32 (%Object*)* @inputInt32_Object, i8* (%Object*)* @inputLine_Object, %Object* (%Object*, i8*)* @print_Object, %Object* (%Object*, i1)* @printBool_Object, %Object* (%Object*, i32)* @printInt32_Object }
@Parent_vtable = constant %struct.ParentVTable { i1 (%Object*)* @inputBool_Object, i32 (%Object*)* @inputInt32_Object, i8* (%Object*)* @inputLine_Object, %Object* (%Object*, i8*)* @print_Object, %Object* (%Object*, i1)* @printBool_Object, %Object* (%Object*, i32)* @printInt32_Object }

declare i8* @malloc(i64)

declare i64 @power(i32, i32)

declare %Object* @newObject()

declare %Object* @initObject(%Object*)

declare i1 @inputBool_Object(%Object*)

declare i32 @inputInt32_Object(%Object*)

declare i8* @inputLine_Object(%Object*)

declare %Object* @print_Object(%Object*, i8*)

declare %Object* @printBool_Object(%Object*, i1)

declare %Object* @printInt32_Object(%Object*, i32)

define %Child* @newChild() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %Parent*
  %2 = call %Parent* @initParent(%Parent* %1)
  %3 = bitcast %Parent* %2 to %Child*
  %4 = call %Child* @initChild(%Child* %3)
  ret %Child* %4
}

define %Child* @initChild(%Child* %0) {
entry:
  %1 = getelementptr inbounds %Child, %Child* %0, i64 0, i32 0
  store %struct.ChildVTable* @Child_vtable, %struct.ChildVTable** %1, align 8
  ret %Child* %0
}

define %GrandParent* @newGrandParent() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %Object*
  %2 = call %Object* @initObject(%Object* %1)
  %3 = bitcast %Object* %2 to %GrandParent*
  %4 = call %GrandParent* @initGrandParent(%GrandParent* %3)
  ret %GrandParent* %4
}

define %GrandParent* @initGrandParent(%GrandParent* %0) {
entry:
  %1 = getelementptr inbounds %GrandParent, %GrandParent* %0, i64 0, i32 0
  store %struct.GrandParentVTable* @GrandParent_vtable, %struct.GrandParentVTable** %1, align 8
  ret %GrandParent* %0
}

define %Main* @newMain() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %Object*
  %2 = call %Object* @initObject(%Object* %1)
  %3 = bitcast %Object* %2 to %Main*
  %4 = call %Main* @initMain(%Main* %3)
  ret %Main* %4
}

define %Main* @initMain(%Main* %0) {
entry:
  %1 = getelementptr inbounds %Main, %Main* %0, i64 0, i32 0
  store %struct.MainVTable* @Main_vtable, %struct.MainVTable** %1, align 8
  ret %Main* %0
}

define i32 @main_Main(%Main* %0) {
entry:
  ret i32 0
}

define %MyClass* @newMyClass() {
entry:
  %0 = call dereferenceable_or_null(128) i8* @malloc(i64 128)
  %1 = bitcast i8* %0 to %Object*
  %2 = call %Object* @initObject(%Object* %1)
  %3 = bitcast %Object* %2 to %MyClass*
  %4 = call %MyClass* @initMyClass(%MyClass* %3)
  ret %MyClass* %4
}

define %MyClass* @initMyClass(%MyClass* %0) {
entry:
  %1 = getelementptr inbounds %MyClass, %MyClass* %0, i64 0, i32 0
  store %struct.MyClassVTable* @MyClass_vtable, %struct.MyClassVTable** %1, align 8
  %2 = call %Child* @newChild()
  %3 = getelementptr inbounds %MyClass, %MyClass* %0, i64 0, i32 1
  store %Child* %2, %GrandParent** %3, align 8
  ret %MyClass* %0
}

define %Parent* @newParent() {
entry:
  %0 = call dereferenceable_or_null(64) i8* @malloc(i64 64)
  %1 = bitcast i8* %0 to %GrandParent*
  %2 = call %GrandParent* @initGrandParent(%GrandParent* %1)
  %3 = bitcast %GrandParent* %2 to %Parent*
  %4 = call %Parent* @initParent(%Parent* %3)
  ret %Parent* %4
}

define %Parent* @initParent(%Parent* %0) {
entry:
  %1 = getelementptr inbounds %Parent, %Parent* %0, i64 0, i32 0
  store %struct.ParentVTable* @Parent_vtable, %struct.ParentVTable** %1, align 8
  ret %Parent* %0
}

define i32 @program_entry() {
entry:
  %0 = call %Main* @newMain()
  %1 = call i32 @main_Main(%Main* %0)
  ret i32 %1
}
