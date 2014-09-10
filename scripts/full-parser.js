$( document ).ready(function() {

	return false;

	var pathname = new String(window.location.search);

	// Don't transform if its not the full list page
	if(pathname != "" && pathname.indexOf("?mode=full") < 0) {
		return false;
	}

	console.log( "Start transformation..." );

	// extract the title of this elog
	var elog_title = $(".title1").html();
	elog_title = elog_title.substring(0, elog_title.lastIndexOf(","));
	elog_title = elog_title.replace(/&nbsp;/g, '');

	// extract the main menu items inside <a href> tags
	// main_menu represents the list of these items
	var main_menu = $(".menu1").html().split("|");

	// extract the view menu links, usually items are "full", "summary" and "threaded"
	var view_menu = $(".menu2a").html().split("|");

	// extract the quick filter menu
	var tmp_filter_menu = $(".menu2b").html().split("<select");

	// last element of this menu is the number of entries
	var last_filter_element = tmp_filter_menu[tmp_filter_menu.length - 1].split("<noscript>");

	// extract the entry count (number of entries)
	var start = last_filter_element[1].indexOf("<b>") + 3;
	var end   = last_filter_element[1].indexOf("</b>");
	var entry_cnt = last_filter_element[1].substr(start, end - start);

	tmp_filter_menu.splice(tmp_filter_menu.length - 1, 1);	// remove the last element because it is going to be formated differently
	tmp_filter_menu.push(last_filter_element[0]);

	// fix the select tags for the quick filter
	var filter_menu = [];
	for(var e in tmp_filter_menu) {
		item = tmp_filter_menu[e];
		if(item.indexOf("</select") > -1) { // this element is a select tag
			item = "<select " + item;
		}

		filter_menu.push(item);
	}

	// extract the pagination data
	var pagination_menu_raw = $(".menu3").html();

	// Pagination exists if this is not undefined, otherwise just skip
	if(pagination_menu_raw !== undefined) {
		pagination_menu_raw = pagination_menu_raw.split(",");

		console.log(pagination_menu_raw);
		var pagination_menu = [];
		for(var idx = 0; idx < pagination_menu_raw.length; idx++) {
			var dots = pagination_menu_raw[idx].indexOf("...");

			if(dots > -1) { // pagination breaks with dots like this ...
				var pagelinks = pagination_menu_raw[idx].split("...");
				var pagelink1 = pagelinks[0];
				var pagelink2 = pagelinks[1];
				pagination_menu.push(pagelink1);
				pagination_menu.push(pagelink2);
			} else {
				var start = pagination_menu_raw[idx].indexOf("<a");
				var end = pagination_menu_raw[idx].indexOf("</a>");
				if(start == -1) { // There are no links here
					pagination_menu.push("");
					continue;
				}
				var pagelink = pagination_menu_raw[idx].substr(start, end - start + 4);
				pagination_menu.push(pagelink);
			}
		}
		console.log(pagination_menu);
	}

	// extract the table headers
	var main_table_headers = [];
	$(".listtitle").each(function() {
		main_table_headers.push($(this).html());
	});

	// extract the entries list
	var table_header_cnt = main_table_headers.length; // Get the number of table headers
	var counter = table_header_cnt;

	/**************************************** HTML ****************************************/

	// replace the header
	$(document.head).html('<meta charset="utf-8">')
					.append('<meta http-equiv="X-UA-Compatible" content="IE=edge">')
					.append('<meta name="viewport" content="width=device-width, initial-scale=1">')
					.append('<meta name="description" content="">')
					.append('<meta name="author" content="">')
					.append('<title>ELOG responsive demo</title>')
					.append('<link href="../bootstrap/css/bootstrap.min.css" rel="stylesheet">')
					.append('<link href="../bootstrap/css/full.css" rel="stylesheet">')
					.append('<!--[if lt IE 9]><script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script><script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script><![endif]-->');

	/**************************************** NAVBAR ****************************************/

	var $toggle_button = $('<button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse"></button>');
	$toggle_button.html('<span class="sr-only">Toggle navigation</span>')
				  .append('<span class="icon-bar"></span>')
				  .append('<span class="icon-bar"></span>')
				  .append('<span class="icon-bar"></span>')

	// navbar header that does not collapse on smaller screens
	var $navbar_header = $('<div class="navbar-header"></div>').html($toggle_button)
															   .append('<a class="navbar-brand" href="summary.html">ELOG</a>');



	// main menu commands
	main_menu_html = '';
	for(var idx = 0; idx < main_menu.length; idx++) {
		main_menu_html += "<li>" + main_menu[idx] + "</li>"
	}
	var $main_menu_commands = $('<ul class="nav navbar-nav navbar-right"></ul>').html(main_menu_html);

	// view dropdown menu
	main_menu_html = '<li class="dropdown"><a href="#" class="dropdown-toggle" data-toggle="dropdown">View <span class="caret"></span></a><ul class="dropdown-menu" role="menu">';
	for(var idx = 0; idx < view_menu.length; idx++) {
		// Get rid of the &nbsp; stuff
		view_menu[idx] = view_menu[idx].replace(/&nbsp;/g, '');

		// This view item has no link so it breaks the design, make it an empty link
		if(view_menu[idx].indexOf("<a href") < 0) {
			view_menu[idx] = "<a href='#'>" + view_menu[idx] + "</a>";
		}

		main_menu_html += "<li>" + view_menu[idx] + "</li>"

		// divide the last item with a divider
		if(idx == view_menu.length - 2)
			main_menu_html += '<li class="divider"></li>'
	}
	main_menu_html += '</ul>'

	// Add the view menu to the navbar
	var $main_menu_view = $('<ul class = "nav navbar-nav navbar-right"></ul>').html(main_menu_html);

	// quick filter commands
	main_menu_html = '';
	for(var idx = 0; idx < filter_menu.length; idx++) {
		item = filter_menu[idx];
		if(item.indexOf("</select") > -1) { // this element is a select tag - maybe do something special
			main_menu_html += '<div class = "nav navbar-form navbar-lower navbar-right">'
			main_menu_html += item;
			main_menu_html += '</div>'
		} else {
			main_menu_html += '<div class = "nav navbar-form navbar-lower navbar-right">'
			main_menu_html += item;
			main_menu_html += '</div>'
		}
	}
	var main_menu_quickfilter = main_menu_html;


	// Extract the links to other logbooks (the tab section)
	var $tabs_div_pills = $('<div class="col-sm-12 col-md-12 elog-tabs"></div>');
	var $tabs_div_normal = $('<div class="col-sm-12 col-md-12 elog-tabs"></div>');
	var $tabs_pills = $('<ul class="nav nav-pills"></ul>');
	var $tabs_normal = $('<ul class="nav nav-tabs"></ul>');

	var top_tabs = '';
	var bottom_tabs = '';
	$("td.tabs").each(function() {
		$(this).children().each(function() {

			if($(this).hasClass('gtab')) {
				top_tabs += "<li>" + $(this).html() + "</li>";
			} else if( $(this).hasClass('sgtab') ) {
				top_tabs += "<li class='active'>" + $(this).html() + "</li>";
			} else if( $(this).hasClass('ltab') ) {
				bottom_tabs += "<li>" + $(this).html() + "</li>";
			} else if( $(this).hasClass('sltab') ) {
				bottom_tabs += "<li class='active'>" + $(this).html() + "</li>";
			}
		});
	});

	// Add the top tabs as pills
	$tabs_pills.html(top_tabs);
	// Add the bottom tabs as regular tabs
	$tabs_normal.html(bottom_tabs);

	// Add it all together
	$tabs_div_pills.html($tabs_pills);
	$tabs_div_normal.html($tabs_normal);
	$tabs_container = $('<div class="container-fluid"><div class="row"></row></div>').html($tabs_div_pills).append($tabs_div_normal);

	// all of the collapsible menu items go here
	var $navbar_collapse = $('<div class="navbar-collapse collapse"></div>').html($main_menu_commands)
																			.append($main_menu_view)
																			.append(main_menu_quickfilter);

	var $navbar_container = $('<div class="container-fluid"></div>').html($navbar_header)
																	.append($navbar_collapse);
	var $main_navbar = $('<div class="navbar navbar-inverse navbar-fixed-top" role="navigation"><div class="container-fluid"></div></div>').html($navbar_container);

	/**************************************** MAIN ****************************************/

	// add table headers
	table_html = "<thead><tr>";
	for(var idx = 0; idx < main_table_headers.length; idx++) {
		table_html += '<th class="info">' + main_table_headers[idx] + '</th>'
	}
	table_html += "</tr></thead>"


	// Print all rows of the table, without the header row
	$("table.listframe tr").has("td").each(function() {

		// Color the attachment rows differently
		$(this).children("td.attachment").addClass("warning");

		table_html += "<tr>"
		table_html += $(this).html();
		table_html += "</tr>"
	});

	var $main_table = $('<table id = "full-list" class="table table-bordered"></table>').html(table_html);
	var $main_table_class = $('<div class="table-responsive">').html($main_table);

	h1_title = '<h1 class="page-header">' + elog_title + '<small> - ' + entry_cnt + '</small></h1>'
	var $main_column = $('<div class="col-sm-12 col-md-12 main"></div>').html(h1_title).append($main_table_class);
	var $main_row = $('<div class="row"></div>').html($main_column);
	var $main_container = $('<div class="container-fluid"></div>').html($main_row);

	// put the complete navbar and body to the html body
	$(document.body).html($tabs_container).append($main_navbar).append($main_container);


	/**************************************** OTHER ****************************************/

	// remove all &nbsp; whitespace as it messes with the design
	$main_navbar.html($main_navbar.html().replace(/&nbsp;/g, ''));

	// add missing classes
	$("select").addClass("form-control");
	$("input[type='text']").addClass("form-control");

});
