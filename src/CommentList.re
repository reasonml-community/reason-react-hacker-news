open Utils;

requireCSS "src/CommentList.css";

module CommentList = {
  include ReactRe.Component;
  type props = {story: StoryData.story_with_comments};
  let name = "CommentList";
  let renderCommentText (textMaybe: option string) =>
    switch textMaybe {
    | Some text => <div dangerouslySetInnerHTML=(dangerousHtml text) />
    | None => textEl "missing comment"
    };
  let rec renderCommentKids story (comment: StoryData.comment_present) =>
    renderCommentList story comment.kids
  and renderComment (id: int) (story: StoryData.story_with_comments) => {
    let commentMaybe = ReadOnlyJSMap.get story.comments id;
    /*
      inside CommentList_disclosureRow
      <img
        alt={open ? 'hide' : 'show'}
        src={open ? require('./disclosure90.png') : require('./disclosure.png')}
        className="CommentList_disclosure CommentList_muted"
      />
     */
    let commentContent =
      switch commentMaybe {
      | Some commentPresentOrDeleted =>
        switch commentPresentOrDeleted {
        | StoryData.CommentPresent comment =>
          <div className="CommentList_comment">
            <div className="CommentList_disclosureRow CommentList_inline">
              <span className="CommentList_muted">
                (textEl (" " ^ fromNow comment.time ^ " by " ^ comment.by))
              </span>
            </div>
            <div className="CommentList_commentBody">
              (renderCommentText comment.text)
              (renderCommentKids story comment)
            </div>
          </div>
        | StoryData.CommentDeleted _ => <div> (textEl "[deleted]") </div>
        }
      | None => raise Exit
      };
    <div key=(string_of_int id)> commentContent </div>
  }
  and renderCommentList story commentIds =>
    switch commentIds {
    | Some ids =>
      let commentList = Array.map (fun id => renderComment id story) ids;
      <div> (ReactRe.arrayToElement commentList) </div>
    | None => <div />
    };
  let render {props} => renderCommentList props.story props.story.kids;
};

include ReactRe.CreateComponent CommentList;

let createElement ::story => wrapProps {story: story};
