$( document ).ready(function()
{
  $("div.headertitle").addClass("page-header");
  $("div.title").addClass("h1");

  $(".dynheader").addClass("alert alert-info"); // expand button for class diagrams
  $(".dyncontent").addClass("panel panel-default");

  $(".fragment").addClass("well"); // panel containing blocks of code

  $(".memitem").addClass("panel panel-info"); // panel containing a member function
  $(".memitem").find(".deprecated").closest(".memitem").addClass("panel-danger"); // change the style of deprecated functions
  $(".deprecated").find(".el")
  .addClass("label label-danger")
  .css("margin-bottom", "5px");
  $(".memproto").addClass("panel-heading"); // panel containing a member function prototype
  $(".memdoc").addClass("panel-body"); // panel containing a member function description

  $("table.params").addClass("table");
  $("table.directory").addClass("table table-striped");
  $("table.fieldtable").addClass("table") // tables where elements like enumerations are shown

  $(".contents").addClass("panel panel-default");

  $("table.memberdecls").addClass("table"); // table listing all member functions
  $(".memberdecls").find(".memSeparator").remove();

  $("span.mlabel").addClass("label label-info"); // labels containing abstract/virtual info

  // navigation bar
  $('li > a[href="index.html"] > span').before("<i class='fa fa-cog'></i> ");
  $('li > a[href="modules.html"] > span').before("<i class='fa fa-square'></i> ");
  $('li > a[href="namespaces.html"] > span').before("<i class='fa fa-bars'></i> ");
  $('li > a[href="annotated.html"] > span').before("<i class='fa fa-list-ul'></i> ");
  $('li > a[href="classes.html"] > span').before("<i class='fa fa-book'></i> ");
  $('li > a[href="inherits.html"] > span').before("<i class='fa fa-sitemap'></i> ");
  $('li > a[href="functions.html"] > span').before("<i class='fa fa-list'></i> ");
  $('li > a[href="functions_func.html"] > span').before("<i class='fa fa-list'></i> ");
  $('li > a[href="functions_vars.html"] > span').before("<i class='fa fa-list'></i> ");
  $('li > a[href="functions_enum.html"] > span').before("<i class='fa fa-list'></i> ");
  $('li > a[href="functions_eval.html"] > span').before("<i class='fa fa-list'></i> ");
  $("div.tabs").addClass("nav nav-tabs");
  $("div.tabs2").addClass("nav nav-tabs");
  $("ul.tablist").addClass("nav nav-pills nav-justified");
  $("ul.tablist").css("margin-top", "0.5em");
  $("ul.tablist").css("margin-bottom", "0.5em");
  $("ul.tablist").css("margin-left", "auto");
  $("ul.tablist").css("margin-right", "auto");
  $("ul.tablist").css("max-width", "600px");
  $("li.current").addClass("active");
  $("#nav-path > ul").addClass("breadcrumb");
  $("#nav-path > ul").css("margin-left", "auto");
  $("#nav-path > ul").css("margin-right", "auto");
  $("#nav-path > ul").css("max-width", "980px");
  $(".navpath").removeClass("navpath");
  $("li.navelem").removeClass("navelem");
  $("ul.tablist").removeClass("tablist");
  $("div.tabs").removeClass("tabs");
  $("div.tabs2").removeClass("tabs2");

  // search box
  $("#MSearchBox").css("position", "relative");
  $(".right").css("position", "relative");
  $(".right").css("right", "0px");
  $(".right").css("left", "141px");
  var results = $("#MSearchResultsWindow");
  $("#MSearchBox").parent().append(results)
  results
    .css("position", "absolute")
    .css("z-index", "500")
    .css("top", "initial")
    .css("margin-top", "8px");

  // detail level
  $("div.levels").css("margin", "0.5em");
  $("div.levels > span").addClass("btn btn-default btn-xs");
  $("div.levels > span").css("margin-right", "0.25em");

});
