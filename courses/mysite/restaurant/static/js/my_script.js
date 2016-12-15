$(document).ready(function(){
    $(".search").click(function(){
        btn = $(this);
        inp = $("#search");
        $.ajax({
            type: "GET",
            url : "/restaurant/search/",
            data: {search: inp.val(), xhr: true},
            success: function(result){

               result = jQuery.parseJSON(result);
             alert(result);
            $(".main_content").remove();
            for(i in result){
                $("#new_content").append
                ('<p><img src = "'+result[i].url+''+result[i].image.url+'"></p><a href = "/restaurant/cold_dish/'+ result[i].id + '" ><p>Назва'+result[i].name+'</p></a><p>Склад :"'+result[i].consist+'"</p><p>Вага:'+result[i].weight+'</p><p>Ціна :'+result[i].price+'</p><form action = "/restaurant/cold_dish/del/'+ result[i].id +'/" method = "POST"><input class  ="button" type = "submit"  value = "Видалити"></form>');
            };
           
        }});
    });
});
                  
      