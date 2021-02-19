// Add module
$(document).ready(function () {
  document
    .getElementById("ticket_code")
    .addEventListener("input", function (e) {
      e.target.value = e.target.value
        .replace(/[^\dA-Z]/g, "")
        .replace(/(.{2})/g, "$1 ")
        .trim();
    });

  // remove notification
  $("#dtbtn").click(function () {
    $("#note").hide();
  });

  //submit ticket

  $(".vote").click(function () {
    //inputs
    var $ticket_code = $("#ticket_code");
    var $candidate = $(this);

    if ($ticket_code.val() == "") {
      swal("Ticket Code?", "Please enter your ticket Code..", "info");
    } else {
      // json object
      var ticket = {
        ticket_code: $ticket_code.val().replace(/\s/g, ""),
      };

      $.ajax({
        type: "POST",
        url: "includes/ajax/check.php",
        data: ticket,
        cache: false,
        success: function (result) {
          if (result == "0") {
            swal(
              "Ticket Code?",
              "You entered an invalid ticket number, try again",
              "info"
            );
          } else {
            swal({
              title: $.trim($candidate.text()),
              text: "is your vote?",
              type: "info",
              confirmButtonColor: "#3085d6",
              cancelButtonColor: "#B3B3B3",
              showCancelButton: true,
              confirmButtonText: "Yes",
              cancelButtonText: "No",
            }).then((result) => {
              if (result.value) {
                var vote = {
                  ticket_code: $ticket_code.val().replace(/\s/g, ""),
                  candidate_id: $candidate.attr("id"),
                  candidate_name: $candidate.text(),
                };

                $.ajax({
                  type: "POST",
                  url: "includes/ajax/add_vote.php",
                  data: vote,
                  cache: false,
                  success: function (result) {
                    if (result == 1) {
                      swal(
                        "Well done!",
                        "Vote Successful",
                        "success"
                      );
                    } else {
                      swal(
                        "Ticket already used",
                        "One ticket, one vote",
                        "info"
                      );
                    }
                  },
                });
              }
            });
          }
        },
      });
    }
  });
});
