
# this file contains generic or project specific string processing methods and classes

# file cleanup before processing

def to_alpha(input: str) -> str:
    if input.isalpha():
        return input

    output = ""
    alphabet = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
    for char in input:
        if alphabet.find(char) > -1:
            output += char
    return output

def remove_multi_spaces(string):
    while string.find("  ") > -1:
        string = string.replace("  ", " ")
    return string

def remove_access_specifiers(input: str) -> str:
    keys = ("public:", "protected:", "private:")
    for key in keys:
        input = input.replace(key, "")
    return input

def remove_sections(string, startChars, endChars, endCharsToLeave = 0):

    while string.find(startChars) > -1:
        startIndex = string.find(startChars)
        endIndex = string[startIndex + 1:].find(endChars) 
        if endIndex < 0:
            return string
        
        endIndex += startIndex + 1
        startStr = string[0:startIndex]
        endStr = string[endIndex + len(endChars) - endCharsToLeave:len(string)]
        string = startStr + endStr

    return string

def remove_section_content(string, startChars, endChars):
    lastIndex = 0
    outString = ""
    while True:
        strToSearch = string[lastIndex + 1:]
        startIndex = strToSearch.find(startChars)
        endIndex = strToSearch[startIndex + 1:].find(endChars) 

        if startIndex < 0 or endIndex < 0:
            break

        outString += strToSearch[:startIndex + 1] + strToSearch[endIndex + startIndex + 1:]
        lastIndex += endIndex
    
    return outString

def remove_comments(string):
    string = remove_sections(string, "//", "\n", 1)
    string = remove_sections(string, "/*", "*/")
    string = remove_sections(string, "/*", "*/")
    return string

def remove_preprocessor_defs(string : str) -> str:
    lines = string.splitlines(True)
    string = ""

    for i, line in enumerate(lines):
        if line.startswith("#"):
            lines.pop(i)

    for line in lines:
        string += line

    return string

def remove_string_content(string):
    string = remove_section_content(string, "\"", "\"")
    return string

def replace_special_chars(string):
    escChars = "\a\b\f\n\r\t\v"
    for char in escChars:
        string = string.replace(char, " ")

    return string

# Scope Content Processing

# removes every combination of the given characters from the input string
def remove_any_from_start(input : str, charsToRemove : str) -> str:
    if len(input) == 0:
        return ""

    output = input
    while True:
        remFirst = False
        for char in charsToRemove:
            if output[0] == char:
                remFirst = True
                output = output[1:]

        if not remFirst:
            break
    
    return output

def is_leaf_scope_from_prefix(prefix: str) -> bool:
    if(prefix == ""):
        return False
    if(prefix.find("class ") > -1):
        return False
    if(prefix.find("struct ") > -1):
        return False
    if(prefix.find("namespace ") > -1):
        return False
    return True

# returns the indexes of the content removed
# like removing a string string section, but remove_brace_content("test(foo())", "(", ")") returns test()
def remove_brace_content(stringToClear : str, braceStartChar = "(", braceEndChar = ")") -> str:
    currentCharIsBraceContent = False
    numBraces = 0 
    newStr = ""

    for char in stringToClear:
        if char == braceStartChar:
            currentCharIsBraceContent = True
            numBraces += 1
            continue # dont remove the brace char
        if char == braceEndChar:
            numBraces += -1
            if numBraces == 0:
                currentCharIsBraceContent = False
        if not currentCharIsBraceContent:
            newStr += char
        
    return newStr

def remove_surrounding_curlys(strToUpdate: str) -> str:
    if(len(strToUpdate) < 1):
        return ""
    if(strToUpdate[0] == "{"):
        assert strToUpdate[-1] == "}"
        return strToUpdate[1:-1]

    return strToUpdate