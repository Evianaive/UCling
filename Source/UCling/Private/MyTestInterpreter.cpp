﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestInterpreter.h"

#include "cling-demo.h"
#include "TestStatic.h"
#include "UCling.h"
#include "cling/Interpreter/Interpreter.h"


// Sets default values
AMyTestInterpreter::AMyTestInterpreter()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProcessString = TEXT("#include \"TestStatic.h\"\nTestStatic::LogSomeThing()");
}

// Called when the game starts or when spawned
void AMyTestInterpreter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyTestInterpreter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyTestInterpreter::Process()
{
	TBaseStructure<FVector>::Get();
	auto& Module = FModuleManager::Get().GetModuleChecked<FUClingModule>(TEXT("UCling"));
	::Process(Module.Interp,StringCast<ANSICHAR>(*ProcessString).Get(),nullptr);
}

void AMyTestInterpreter::ProcessCommand()
{
	auto& Module = FModuleManager::Get().GetModuleChecked<FUClingModule>(TEXT("UCling"));
	::ProcessCommand(Module.Interp, StringCast<ANSICHAR>(*ProcessString).Get());
}

void AMyTestInterpreter::TestCallByUE()
{
	TestStatic::LogSomeThing();
}

void AMyTestInterpreter::TestTArrayStruct()
{
	ProcessString =
		TEXT(
		"#include \"Containers/Array.h\"\n"
		"#include \"TestStatic.h\"\n"
		"struct StructWithTArray{\n"
		"	TArray<int32> Ints;\n"
		"};\n"
		"StructWithTArray Test;\n"
		"Test.Ints.Add(5);\n"
		"TestStatic::LogSomeThing(&Test.Ints[0]);");
}

