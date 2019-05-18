#ifndef GLOBAL_H
#define GLOBAL_H

#define PARSER_NAMESPACE parser

#ifdef PARSER_NAMESPACE
#   define TOOSKA_BEGIN_NAMESPACE(module) namespace tooska { namespace module {
#   define TOOSKA_END_NAMESPACE } }
#else
#   define TOOSKA_BEGIN_NAMESPACE
#   define TOOSKA_END_NAMESPACE
#endif

#include <string>

namespace tooska {
enum class print_type {
    compact,
    formatted
};
}

TOOSKA_BEGIN_NAMESPACE(core)
enum class html_tag_type {
    a, // Defines a hyperlink
    abbr, // Defines an abbreviation or an acronym
    acronym, // Not supported in HTML5. Use <abbr> instead. Defines an acronym
    address, // Defines contact information for the author/owner of a document
    applet, // Not supported in HTML5. Use <embed> or <object> instead. Defines an embedded applet
    area, // Defines an area inside an image-map
    article, // Defines an article
    aside, // Defines content aside from the page content
    audio, // Defines sound content
    b, // Defines bold text
    base, // Specifies the base URL/target for all relative URLs in a document
    basefont, // Not supported in HTML5. Use CSS instead. Specifies a default color, size, and font for all text in a document
    bdi, // Isolates a part of text that might be formatted in a different direction from other text outside it
    bdo, // Overrides the current text direction
    big, // Not supported in HTML5. Use CSS instead. Defines big text
    blockquote, // Defines a section that is quoted from another source
    body, // Defines the document's body
    br, // Defines a single line break
    button, // Defines a clickable button
    canvas, // Used to draw graphics, on the fly, via scripting (usually JavaScript)
    caption, // Defines a table caption
    center, // Not supported in HTML5. Use CSS instead. Defines centered text
    cite, // Defines the title of a work
    code, // Defines a piece of computer code
    col, // Specifies column properties for each column within a <colgroup> element
    colgroup, // Specifies a group of one or more columns in a table for formatting
    data, // Links the given content with a machine-readable translation
    datalist, // Specifies a list of pre-defined options for input controls
    dd, // Defines a description/value of a term in a description list
    del, // Defines text that has been deleted from a document
    details, // Defines additional details that the user can view or hide
    dfn, // Represents the defining instance of a term
    dialog, // Defines a dialog box or window
    dir, // Not supported in HTML5. Use <ul> instead. Defines a directory list
    div, // Defines a section in a document
    dl, // Defines a description list
    dt, // Defines a term/name in a description list
    em, // Defines emphasized text
    embed, // Defines a container for an external (non-HTML) application
    fieldset, // Groups related elements in a form
    figcaption, // Defines a caption for a <figure> element
    figure, // Specifies self-contained content
    font, // Not supported in HTML5. Use CSS instead. Defines font, color, and size for text
    footer, // Defines a footer for a document or section
    form, // Defines an HTML form for user input
    frame, // Not supported in HTML5. Defines a window (a frame) in a frameset
    frameset, // Not supported in HTML5. Defines a set of frames
    h1, // Defines HTML headings 1
    h2, // Defines HTML headings 2
    h3, // Defines HTML headings 3
    h4, // Defines HTML headings 4
    h5, // Defines HTML headings 5
    h6, // Defines HTML headings 6
    head, // Defines information about the document
    header, // Defines a header for a document or section
    hr, // Defines a thematic change in the content
    html, // Defines the root of an HTML document
    i, // Defines a part of text in an alternate voice or mood
    iframe, // Defines an inline frame
    img, // Defines an image
    input, // Defines an input control
    ins, // Defines a text that has been inserted into a document
    kbd, // Defines keyboard input
    label, // Defines a label for an <input> element
    legend, // Defines a caption for a <fieldset> element
    li, // Defines a list item
    link, // Defines the relationship between a document and an external resource (most used to link to style sheets)
    main, // Specifies the main content of a document
    map, // Defines a client-side image-map
    mark, // Defines marked/highlighted text
    meta, // Defines metadata about an HTML document
    meter, // Defines a scalar measurement within a known range (a gauge)
    nav, // Defines navigation links
    noframes, // Not supported in HTML5. Defines an alternate content for users that do not support frames
    noscript, // Defines an alternate content for users that do not support client-side scripts
    object, // Defines an embedded object
    ol, // Defines an ordered list
    optgroup, // Defines a group of related options in a drop-down list
    option, // Defines an option in a drop-down list
    output, // Defines the result of a calculation
    p, // Defines a paragraph
    param, // Defines a parameter for an object
    picture, // Defines a container for multiple image resources
    pre, // Defines preformatted text
    progress, // Represents the progress of a task
    q, // Defines a short quotation
    rp, // Defines what to show in browsers that do not support ruby annotations
    rt, // Defines an explanation/pronunciation of characters (for East Asian typography)
    ruby, // Defines a ruby annotation (for East Asian typography)
    s, // Defines text that is no longer correct
    samp, // Defines sample output from a computer program
    script, // Defines a client-side script
    section, // Defines a section in a document
    select, // Defines a drop-down list
    small, // Defines smaller text
    source, // Defines multiple media resources for media elements (<video> and <audio>)
    span, // Defines a section in a document
    strike, // Not supported in HTML5. Use <del> or <s> instead. Defines strikethrough text
    strong, // Defines important text
    style, // Defines style information for a document
    sub, // Defines subscripted text
    summary, // Defines a visible heading for a <details> element
    sup, // Defines superscripted text
    svg, // Defines a container for SVG graphics
    table, // Defines a table
    tbody, // Groups the body content in a table
    td, // Defines a cell in a table
    template_, // Defines a template
    textarea, // Defines a multiline input control (text area)
    tfoot, // Groups the footer content in a table
    th, // Defines a header cell in a table
    thead, // Groups the header content in a table
    time, // Defines a date/time
    title, // Defines a title for the document
    tr, // Defines a row in a table
    track, // Defines text tracks for media elements (<video> and <audio>)
    tt, // Not supported in HTML5. Use CSS instead. Defines teletype text
    u, // Defines text that should be stylistically different from normal text
    ul, // Defines an unordered list
    var, // Defines a variable
    video, // Defines a video or movie
    wbr, // Defines a possible line-break
};

static inline std::string html_tag_str(const html_tag_type &type) {
    switch (type) {
    case html_tag_type::a: 	return "a";
    case html_tag_type::abbr: 	return "abbr";
    case html_tag_type::acronym: 	return "acronym";
    case html_tag_type::address: 	return "address";
    case html_tag_type::applet: 	return "applet";
    case html_tag_type::area: 	return "area";
    case html_tag_type::article: 	return "article";
    case html_tag_type::aside: 	return "aside";
    case html_tag_type::audio: 	return "audio";
    case html_tag_type::b: 	return "b";
    case html_tag_type::base: 	return "base";
    case html_tag_type::basefont: 	return "basefont";
    case html_tag_type::bdi: 	return "bdi";
    case html_tag_type::bdo: 	return "bdo";
    case html_tag_type::big: 	return "big";
    case html_tag_type::blockquote: 	return "blockquote";
    case html_tag_type::body: 	return "body";
    case html_tag_type::br: 	return "br";
    case html_tag_type::button: 	return "button";
    case html_tag_type::canvas: 	return "canvas";
    case html_tag_type::caption: 	return "caption";
    case html_tag_type::center: 	return "center";
    case html_tag_type::cite: 	return "cite";
    case html_tag_type::code: 	return "code";
    case html_tag_type::col: 	return "col";
    case html_tag_type::colgroup: 	return "colgroup";
    case html_tag_type::data: 	return "data";
    case html_tag_type::datalist: 	return "datalist";
    case html_tag_type::dd: 	return "dd";
    case html_tag_type::del: 	return "del";
    case html_tag_type::details: 	return "details";
    case html_tag_type::dfn: 	return "dfn";
    case html_tag_type::dialog: 	return "dialog";
    case html_tag_type::dir: 	return "dir";
    case html_tag_type::div: 	return "div";
    case html_tag_type::dl: 	return "dl";
    case html_tag_type::dt: 	return "dt";
    case html_tag_type::em: 	return "em";
    case html_tag_type::embed: 	return "embed";
    case html_tag_type::fieldset: 	return "fieldset";
    case html_tag_type::figcaption: 	return "figcaption";
    case html_tag_type::figure: 	return "figure";
    case html_tag_type::font: 	return "font";
    case html_tag_type::footer: 	return "footer";
    case html_tag_type::form: 	return "form";
    case html_tag_type::frame: 	return "frame";
    case html_tag_type::frameset: 	return "frameset";
    case html_tag_type::h1: 	return "h1";
    case html_tag_type::h2: 	return "h2";
    case html_tag_type::h3: 	return "h3";
    case html_tag_type::h4: 	return "h4";
    case html_tag_type::h5: 	return "h5";
    case html_tag_type::h6: 	return "h6";
    case html_tag_type::head: 	return "head";
    case html_tag_type::header: 	return "header";
    case html_tag_type::hr: 	return "hr";
    case html_tag_type::html: 	return "html";
    case html_tag_type::i: 	return "i";
    case html_tag_type::iframe: 	return "iframe";
    case html_tag_type::img: 	return "img";
    case html_tag_type::input: 	return "input";
    case html_tag_type::ins: 	return "ins";
    case html_tag_type::kbd: 	return "kbd";
    case html_tag_type::label: 	return "label";
    case html_tag_type::legend: 	return "legend";
    case html_tag_type::li: 	return "li";
    case html_tag_type::link: 	return "link";
    case html_tag_type::main: 	return "main";
    case html_tag_type::map: 	return "map";
    case html_tag_type::mark: 	return "mark";
    case html_tag_type::meta: 	return "meta";
    case html_tag_type::meter: 	return "meter";
    case html_tag_type::nav: 	return "nav";
    case html_tag_type::noframes: 	return "noframes";
    case html_tag_type::noscript: 	return "noscript";
    case html_tag_type::object: 	return "object";
    case html_tag_type::ol: 	return "ol";
    case html_tag_type::optgroup: 	return "optgroup";
    case html_tag_type::option: 	return "option";
    case html_tag_type::output: 	return "output";
    case html_tag_type::p: 	return "p";
    case html_tag_type::param: 	return "param";
    case html_tag_type::picture: 	return "picture";
    case html_tag_type::pre: 	return "pre";
    case html_tag_type::progress: 	return "progress";
    case html_tag_type::q: 	return "q";
    case html_tag_type::rp: 	return "rp";
    case html_tag_type::rt: 	return "rt";
    case html_tag_type::ruby: 	return "ruby";
    case html_tag_type::s: 	return "s";
    case html_tag_type::samp: 	return "samp";
    case html_tag_type::script: 	return "script";
    case html_tag_type::section: 	return "section";
    case html_tag_type::select: 	return "select";
    case html_tag_type::small: 	return "small";
    case html_tag_type::source: 	return "source";
    case html_tag_type::span: 	return "span";
    case html_tag_type::strike: 	return "strike";
    case html_tag_type::strong: 	return "strong";
    case html_tag_type::style: 	return "style";
    case html_tag_type::sub: 	return "sub";
    case html_tag_type::summary: 	return "summary";
    case html_tag_type::sup: 	return "sup";
    case html_tag_type::svg: 	return "svg";
    case html_tag_type::table: 	return "table";
    case html_tag_type::tbody: 	return "tbody";
    case html_tag_type::td: 	return "td";
    case html_tag_type::template_: 	return "template";
    case html_tag_type::textarea: 	return "textarea";
    case html_tag_type::tfoot: 	return "tfoot";
    case html_tag_type::th: 	return "th";
    case html_tag_type::thead: 	return "thead";
    case html_tag_type::time: 	return "time";
    case html_tag_type::title: 	return "title";
    case html_tag_type::tr: 	return "tr";
    case html_tag_type::track: 	return "track";
    case html_tag_type::tt: 	return "tt";
    case html_tag_type::u: 	return "u";
    case html_tag_type::ul: 	return "ul";
    case html_tag_type::var: 	return "var";
    case html_tag_type::video: 	return "video";
    case html_tag_type::wbr: 	return "wbr";
    }
    return std::string();
}
inline bool operator ==(std::string &str, html_tag_type &t) {
    return str == html_tag_str(t);
}
inline bool operator !=(std::string &str, html_tag_type &t) {
    return !(str == t);
}

TOOSKA_END_NAMESPACE

#endif // GLOBAL_H
