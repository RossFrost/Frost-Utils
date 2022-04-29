
/**
 * @param {document.querySelector} element 
 */

function checkElementExistence(element) {
    if (typeof element != "undefined") {
        return true
    }

    else {
        return false
    }
}


/**
 * 
 * @param {[[string, {}]]} elements [[element, {attribute: value}], ...]
 * @param {string} location Elements location in document
 */
 
function creatElements(elements, location) {
    for (element of elements) {
        console.log(element)
        let created_element = document.createElement(element[0])

        for ([key, value] of Object.entries(element[1])) {
            console.log(key, value)
            let bin = created_element.setAttribute(key, value)
        }
        location.append(created_element)
    }
}

/**
 * 
 * @param {string} dependents A liste of dependents to wait to load
 * @returns "ready"
 */

//Syntax = []
function load_dependents(dependents) {
    for (dependent in dependents) {
        let object = document.querySelector(dependents[dependent])
        if (checkElementExistence(object) == true) {
            object.on("load", function() {
                return
            })
        }

        else {
            console.log(dependent + " not found")
        }
    }
    return "ready"    
}


function get_URL() {
    return window.location + "//" + window.location.protocol
}


/**
 * @param {string} element
 * @param {string} event_
 * @param {function} func
 */


function single_listener(element, event_, func) {
    let queried_element = document.querySelector(element) 
    let event__ = queried_element.addEventListener(event_, func)
    return event__
}

/**
 * @param {[[string, string]]} elements [[element, event], ...]
 * @param {string} event_
 * @param {function} func
 */

function mutli_listener(elements, func) {
    for (item in set) {
        let element = elements[item][0]
        let event_ = elements[item][1]
        let element_ = document.querySelector(element)

        if (checkElementExistence(element) == true) {
            let event__ = queried_element.addEventListener(event_, func)

        }
    }
}