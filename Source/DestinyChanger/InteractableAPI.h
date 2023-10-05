//制作日：2023/07/28　制作者：トウ　更新内容：InteractのAPIを作成

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableAPI.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableAPI : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DESTINYCHANGER_API IInteractableAPI
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Interact(AActor* Caller = nullptr) = 0;

};
