/**
 * @param {document.querySelector} element 
 */


function checkElementExistence(element) {
    if (typeof element != "undefined") {
        return true
    }

    return false
}


function query_select(element, scope = "none", half_options = "ceil") {
    switch (scope) {
        case "none":
            if (Array.isArray(element) == true) {
                return document.querySelector(element.toString())}
            return document.querySelector(element)

        case "all":
            return document.querySelectorAll(element)

        case "middle":
            function halves_maths(length, default_ = "array") {
                let half = (length.length / 2) - 1
                if (half_options == "floor") {return Math.floor(half)}
                return Math.ceil(half)}
                
            if (scope = "all") {document.querySelectorAll(element[halves_maths(element)])}
            console.log(scope + " has to be set to all")


    }

    console.log(scope + " is an invalid scope.")
}


/**
 * 
 * @param {[[string, {}]]} elements [[element, {attribute: value}], ...]
 * @param {string} location Elements location in document
 */
 
function create_elements(elements, location) {
    for (var element of elements) {
        var  created_element = document.createElement(element[0]); var key; var value;

        for ([key, value] of Object.entries(element[1])) {
            if (key == "text") {created_element.appendChild(document.createTextNode(value)); continue}
            let bin = created_element.setAttribute(key, value)}
        location.append(created_element)
    }
}

/**
 * 
 * @param {string} dependents A list of dependents to wait to load
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
    return window.location.origin
}


/**
 * @param {string} element
 * @param {string} event_
 * @param {function} func
 */


function single_listener(element, event_, func) {
    let event__ = query_select(element).addEventListener(event_, func)
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
        let list_of_listeners = []

        if (checkElementExistence(element) == true) {
            let event_listener = query_select(element).addEventListener(event_, func)
            list_of_listeners.push(event_listener)
        }
    }

    return list_of_listeners
}

export {
        checkElementExistence, 
        query_select, mutli_listener, 
        single_listener, get_URL, 
        load_dependents,
        create_elements
       };


                   
