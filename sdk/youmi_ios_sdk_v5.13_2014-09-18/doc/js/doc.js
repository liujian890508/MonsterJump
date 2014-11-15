$(document).ready(function() {
    // sidebar
    $('a.sub-header').click(function(){
        if ($(this).find('i').hasClass('icon-chevron-down')) {
            $(this).find('i').removeClass('icon-chevron-down').addClass('icon-chevron-right').end().next().slideUp();
            return false;
        }
        if ($(this).find('i').hasClass('icon-chevron-right')) {
            $(this).find('i').removeClass('icon-chevron-right').addClass('icon-chevron-down').end().next().slideDown();
            return false;
        }
    });
});
