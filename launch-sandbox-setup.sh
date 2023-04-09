source setup-sanbox.sh
source common-variables.sh

setupAvrDude

if [[ $? -gt 0 ]]; then 
    echo -e "${RED_C} --MajorTask@SetupAvrDude : Failed setting up avrdude, check your connection and your storage"
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@SetupAvrDude : avrdude Successfully settled up and ready to run."
fi

echo -e ${RESET_Cs}

setupCURL

if [[ $? -gt 0 ]]; then 
    echo -e "${RED_C} --MajorTask@SetupCURL : Failed setting up CURL, check your connection and your storage"
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@SetupCURL : Curl Successfully settled up and ready to run."
fi

echo -e ${RESET_Cs}

downloadAvrToolChain

if [[ $? -gt 0 ]]; then 
    echo -e "${RED_C} --MajorTask@Download-AvrGCC : Failed downloading avr toolchains, check your connection and your storage."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Download-AvrGCC : Avr toolchains archive is downloaded successfully."
fi

echo -e ${RESET_Cs}

extractCompressedFile $avrgcc_compressed

if [[ $? -gt 0 ]]; then
    echo -e "${RED_C} --MajorTask@Extract-AvrGCC : Failed extracting avr toolchains, check your storage and your permssions."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Extract-AvrGCC : Avr toolchains is extracted successfully."
fi

echo -e ${RESET_Cs}

deleteAvrToolchainsArchive

if [[ $? -gt 0 ]]; then
    echo -e "${RED_C} --MajorTask@Release-AVR-GCC-Archive : Failed deleting avr-gcc archive, archive not found."
	exit $?
else 
    echo -e "${GREEN_C} --MajorTask@Release-AVR-GCC-Archive : AVR-GCC archive has been deleted successfully."
fi

echo -e ${RESET_Cs}

